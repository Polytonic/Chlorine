## [Chlorine](https://github.com/Polytonic/) :: [Swap](https://github.com/Polytonic/Chlorine/tree/master/examples/swap)
This is the simplest example of how to use Chlorine. We start by including the Chlorine header.

```c++
#include "chlorine.hpp"
```

Now we create some dummy data. While this example uses `std::vector` for brevity, you can freely mix and match containers of any type. This can be useful if you need to mix bounded and unbounded array types.

```c++
// Create Some Data
std::vector<float> spam(10, 3.1415f);
std::vector<float> eggs(10, 2.7182f);
```

Next, we create a Chlorine Worker, using the filename constructor, which takes a path to an OpenCL kernel file.

```c++
// Initialize a Chlorine Worker
ch::Worker worker("swap.cl");
```

Alternately, if you want to create your workers independently of loading kernels, you can instead use the overloaded stream operators in conjunction with the `::read()` helper.

```c++
// Initialize a Chlorine Worker
ch::Worker worker;
// Read a Kernel File
std::string kernel = ch::read("swap.cl");
// Compile the Kernel Functions
worker >> kernel;
```

Now that our worker is aware of kernel functions, we can simply invoke `Worker::call(kernel_function, ... )` with the first argument being the name of the kernel function you wish to call, followed by the same arguments (in the same order!) as the kernel function.

```c++
// Call the Swap Function in the Given Kernel
worker.call("swap", spam, eggs);
```

After this completes, data is automatically written back to the same memory locations allocated by your program.

```c++
// Host Containers Are Automatically Updated
std::cout << "Spam: " << spam[0] << "\n"; // 2.7182
std::cout << "Eggs: " << eggs[0] << "\n"; // 3.1415
```

Don't take my word for it though! If you build and run this example, you'll see that the values in each array have been swapped. In order for this to compile, we need to link with the system installation of OpenCL. We also need to pass `-std=c++11` to the compiler to enable variadic templating in Chlorine. You should end up with something like this:

```bash
$ clang++ -std=c++11 swap.cpp -lOpenCL
```

Kernel files are written in a variant of the C programming language. While I won't go into detail about it here, I hope this serves as a valuable demonstration in how Chlorine may be used to easily port code to run in parallel.

### Profiling

```c++
// Original Call
worker.call("swap", spam, eggs);

// New Call
auto event = worker.call("swap", spam, eggs);
```

As of [1d7769](https://github.com/Polytonic/Chlorine/tree/1d776984a11466cfd742bec2af0ff7b278a4479a), Chlorine now returns the OpenCL event associated with the kernel function call. This allows you to recover profiling data, such as how much time was spent executing the kernel function, as well as the idling time. For simplicity, we return the entire OpenCL object rather than adding a new function call to our API. This should be a non-breaking change for the most part.

```c++
// Print Some Profiling Data
std::cout << "Elapsed Time: " << ch::elapsed(event) << "ns\n";
```

To make things easier, we also added a new helper function `ch::elapsed()` which accepts an OpenCL event and returns the elapsed time spent on your kernel function. This helper preserves the nanosecond resolution offered by the OpenCL API and is merely a convenience wrapper.
