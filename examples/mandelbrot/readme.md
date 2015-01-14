## [Chlorine](https://github.com/Polytonic/) :: [Mandelbrot](https://github.com/Polytonic/Chlorine/tree/master/examples/mandelbrot)
![The Mandelbrot Set](http://i.imgur.com/Y0ZIvgV.png)

## Overview
[The Mandelbrot Set](http://en.wikipedia.org/wiki/mandelbrot_set) is a subset of complex numbers defined by an equation that, when plotted on the complex plane, forms a fractal. One simple way of calculating the Mandelbrot Set is to iterate the series *z<sub>M</sub>* until *|M| > 2* for each *M* in the complex numbers.  If the computation doesn't reach this point, then *M* is in the Mandelbrot Set. A set estimation can be achieved by iterating a finite, large amount of times. This type of computation is easy to run in parallel, since each candidate can be run independently.

## Walkthrough
To compare and contrast, we implement the Mandelbrot Set to run both on a traditional processor, as well as using Chlorine. To demonstrate, here are both prototypes for `solve_mandelbrot()`. Other than the OpenCL memory tags and use of pointers, they are otherwise very similar.

```c++
void solve_mandelbrot(std::vector<float> const & real,
                      std::vector<float> const & imag,
                      int iterations,
                      std::vector<int> & result)
```
```opencl
__kernel void solve_mandelbrot(__global float const * real,
                               __global float const * imag,
                               int iterations,
                               __global int * result)
```


The function `solve_mandelbrot()` accepts a vector of real and imaginary points (representing *M<sub>i</sub> = x<sub>i</sub> + y<sub>i</sub>* j), the number of iterations to run the series before assuming the number is in the set, and a vector to store the output. Look at both the kernel and host algorithm implementation and confirm for yourself that they are, in fact, identical.

```c++
float x = real[i]; // Real Component
float y = imag[i]; // Imaginary Component
int   n = 0;       // Tracks Color Information

// Compute the Mandelbrot Set
while ((x * x + y * y <= 2 * 2) && n < iterations)
{
    float xtemp = x * x - y * y + real[i];
    y = 2 * x * y + imag[i];
    x = xtemp;
    n++;
}

// Write Results to Output Arrays
result[i] = x * x + y * y <= 2 * 2 ? -1 : n;
```

The key difference here is that we must iterate through the entire image using a `for` loop on the host, while in OpenCL, we can remove the `for` loop altogether, and instead retrieve the index by querying the device.

```c++
// Host Code
for(unsigned int i = 0; i < real.size(); i++)
// Chlorine Kernel
unsigned int i = get_global_id(0);
```
Let's see how this works in practice, by defining some settings for the Mandelbrot Set we're going to generate:

- We set a maximum number of iterations at a somewhat-large number to be near accurate.
- Since the Mandelbrot Set is completely contained within the unit circle of radius 2, we calculate only for the circumscribed square.
- The step value is set so the resulting image is 1000px x 1000px, around the size of a computer screen.

```c++
    // Define Mandelbrot Settings
    int iterations = 10000;
    float x_min  = -2f;
    float x_max  =  2f;
    float y_min  = -2f;
    float y_max  =  2f;
    float x_step = .002f;
    float y_step = .002f;
```

Next, we turn the points in this range into a single vector of points to test, by linearizing the grid to make it easier to pass in. The stride is recorded so the result can be put back into a grid.

```cpp
    // Create Linear Vector of Coordinates
    unsigned int stride = (x_max - x_min) / x_step + 2;
    std::vector<float> reals;
    std::vector<float> imags;
    for(float y = y_min; y < y_max; y += y_step)
    for(float x = x_min; x < x_max; x += x_step)
    {
        reals.push_back(x);
        imags.push_back(y);
    }
```

For the CPU, we first make an output vector to pass into the function. We then record the start time, call the function, then record the end time. By recording the start and end times, we can compare the time taken between the CPU and Chlorine, for a rough performance benchmark.

```cpp
    // Compute the Mandelbrot Set on the CPU
    std::vector<int> cpu_ans(reals.size());
    clock_t cpu_begin = clock();
    solve_mandelbrot(reals, imags, iterations, cpu_ans);
    clock_t cpu_end = clock();
```

We first create a worker that will load the OpenCL runtime and compile the kernel code. Note that calling Chlorine is very similar to calling traditional functions: the function name is passed to the `call()` function instead of being called directly. Everything else is exactly the same.

```cpp
    // Compute the Mandelbrot Set Using Chlorine
    std::vector<int> cl_ans(reals.size());
    ch::Worker benoit("mandelbrot.cl");
    clock_t cl_begin = clock();
    benoit.call("solve_mandelbrot", reals, imags, iterations, cl_ans);
    clock_t cl_end = clock();
```

As a matter of good practice, we compare the output to ensure that we're really getting the same answer. Note that due to floating point precision limitations, there may be a small degree of error between the host and OpenCL outputs.

```cpp
    // Compare the Output Arrays
    unsigned int error_count = 0;
    for(unsigned int i = 0; i < cpu_ans.size(); i++)
        if (cpu_ans[i] != cl_ans[i])
            error_count++;
```

From here, we write the image to the (very simple) [PPM](http://en.wikipedia.org/wiki/Netpbm_format) format, which you can display using [ImageMagick](http://www.imagemagick.org/), [Adobe Photoshop](www.adobe.com/products/photoshop.html), or similar. If all goes well, you should see the same image as the one at the top of this document.
