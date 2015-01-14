The Mandelbrot Set
=======================

The Mandelbrot Set is a subset of complex numbers defined by an equation that, when plotted on the complex plane, forms a fractal.  The definition is as follows:

Define the series *z<sub>M</sub>* as follows for all *M*:

*z<sub>M,0</sub> = 0*

*z<sub>M,n+1</sub> = z<sub>M,n</sub><sup>2</sup>+M*

The Mandelbrot Set is the set encompassing all *M* such that *z<sub>M,n</sub>* is bounded as *n* goes to infinity. (*z<sub>M,n</sub>* does not go to infinity in any direction).
When in the complex plane, a complex number *a+b* j can be represented as a vector *ai&#770; + bj&#770;*.  Squaring such a complex number results in a vector with twice the length and double the angle from 0°.  For a complex number *M*, with *|M|>1*, we find *z<sub>M,1</sub> = M*, and *z<sub>M,2</sub> = M<sup>2</sup>+M*.  We can derive an lower-bound length for *z<sub>M,2</sub>* as *|M|<sup>2</sup>-|M|*.  If *|z<sub>2</sub>|>|z<sub>1</sub>|* in this case, the series will increase without bound, since the squared length increases faster than it can be subtracted away.  Thus, we can derive an upper bound for the Mandelbrot Set as 

*|M|<sup>2</sup>-|M| = |M|*

*|M| = 0,2*

*|M| ≤ 2*

Computation
----

One simple way of calculating the Mandelbrot Set is to iterate the series *z<sub>M</sub>* until *|M| > 2* for each *M* in the complex numbers.  If the computation doesn't reach this point, then *M* is in the Mandelbrot Set.  Unfortunately, this would require solving the halting problem, which is not computable.  Luckily, a set estimation can be achieved by iterating a finite, large amount of times.  This type of computation is highly parallelizabile, since each candidate can be run independently.

Source Code
---
The source code to run this simulation is located in the ./examples/Mandelbrot folder
The following source code is provided to compute the Mandelbrot Set on both the CPU and on the GPU using Chlorine.

```cpp
void solve_mandelbrot(std::vector<float> const & real,
                      std::vector<float> const & imag,
                      int iterations,
                      std::vector<int> & result)
{
    for(unsigned int i = 0; i < real.size(); i++)
    {
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
    }
}
```

The function ``void solve_mandelbrot`` is the main algorithm function, taking in a vector of real and imaginary points (representing *M<sub>i</sub> = x<sub>i</sub> + y<sub>i</sub>* j), the number of iterations to run the series before assuming the number is in the set, and a vector to store the output.


```opencl
__kernel void solve_mandelbrot(__global float const * real,
                               __global float const * imag,
                               int iterations,
                               __global int * result)
{
    // Get Parallel Index
    unsigned int i = get_global_id(0);

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
}
```

The algorithm for Chlorine is exactly the same as for the CPU, except it receives an index from the machine instead of looping through each input.




The main function in mandelbrot.cpp runs the simulation both on the CPU and through Chlorine.

Going through this function:

```cpp
    // Define Mandelbrot Settings
    int iterations = 10000;
    float x_min  = -2f;
    float x_max  =  2f;
    float y_min  = -2f;
    float y_max  =  2f;
    float x_step = .002f;
    float y_step = .002f;
```

We first start by defining the parameters of the Mandelbrot function:
* We set a maximum number of iterations at a somewhat-large number to be near accurate.
* Since the Mandelbrot Set is completely contained within the unit circle of radius 2, we calculate only for the circumscribed square.
* The step value is set so the resulting image is 1000px x 1000px, around the size of a computer screen

Next:

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

We now turn the points in this range into a single vector of points to test, by linearizing the grid to make it easier to pass it in. The stride is recorded so the result can be put back into a grid.

```cpp
    // Compute the Mandelbrot Set on the CPU
    std::vector<int> cpu_ans(reals.size());
    clock_t cpu_begin = clock();
    solve_mandelbrot(reals, imags, iterations, cpu_ans);
    clock_t cpu_end = clock();
```

For the CPU, we first make an output vector to pass into the function. We then record the start time, call the function, then record the end time. By recording the start and end times, we can compare the time taken between the CPU and Chlorine, and hopefully demonstrate the vastly improved speed.

```cpp
    // Compute the Mandelbrot Set Using Chlorine
    std::vector<int> cl_ans(reals.size());
    ch::Worker benoit("mandelbrot.cl");
    clock_t cl_begin = clock();
    benoit.call("solve_mandelbrot", reals, imags, iterations, cl_ans);
    clock_t cl_end = clock();
```

Notice that calling Chlorine is very similar to calling the regular CPU function.  We first have to create a "Worker", that will load the .cl file and set OpenCL up for the current machine. Calling the function is similar, the function name is passed into the "call" function instead of being called directly, but the syntax is pretty much just as simple as the CPU function.  Everything else is exactly the same.

```cpp
    // Compare the Output Arrays
    unsigned int error_count = 0;
    for(unsigned int i = 0; i < cpu_ans.size(); i++)
        if (cpu_ans[i] != cl_ans[i])
            error_count++;
```

To show that the two functions work similarly, the results of each function are compared. Note that some machines and GPUs round slightly different than others, so there may be a slight difference between outputs.

```cpp
    // Reshape the Output Array to 2D for Drawing
    std::vector<std::vector<int>> ans_grid;
    for(unsigned int i = 0; i < reals.size() / stride; i++)
        ans_grid.push_back(std::vector<int>(
                           cl_ans.begin() + (i      * stride),
                           cl_ans.begin() + (i + 1) * stride));
```

We next turn the linear vector of outputs back into the original grid.

```cpp
    // Write the Mandelbrot Set to File
    ppm_draw("mandelbrot.ppm", ans_grid);
```

We use this function (covered later) to draw to a .ppm file

```cpp
    // Print Statistics
    std::cout << "CPU Time: " << (float) (cpu_end - cpu_begin) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "GPU Time: " << (float) (cl_end - cl_begin)   / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "Error: "    << (float) error_count * 100 / cpu_ans.size() << "%" << std::endl;
```

Finally, we print out the resultant computing time for each calculation and the percent error.

Drawing
---

```cpp
    std::ofstream fd(filename);
```

First, we create the output stream to the .ppm image file,

```cpp
    unsigned int iterations = 50;
```

We cheat with the maximum color for printing, since linearly printing the number of iterations for n > 200 brings a non-colorful picture.

```cpp
    fd << "P6"
       << " " << grid[0].size()
       << " " << grid.size()
       << " " << 255
       << std::endl;
```
Here we simply write the header for the .ppm file.

The ppm format for binary color pictures starts with "P6", then inputs the width, height, and maximum number for r, g, and b (255 here).

```cpp
    for(auto &i : grid)
    for(auto &j : i)
    {
        unsigned char r, g, b;
        if(j == -1) { r = 0; g = 0; b = 0; }
        else
        {
            r = (j * 255 / iterations);
            g = r;
            b = 255;
        }

        // Write Colors to File
        fd << r << g << b;
    }
```
Now, we write each pixel color to the grid (where *j* is the pixel value).  To make the color different highlights of blue, we set full blue, and give "iterations" as a shade of blue, with 0 being pure blue and 50 being pure white.  We then write the resultant colors to the file.

From this, we can write the full image file out.
