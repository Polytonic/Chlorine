# [Chlorine](http://polytonic.github.io/Chlorine/)
[![Build Status](http://img.shields.io/travis/Polytonic/Chlorine/master.svg?style=flat-square)](https://travis-ci.org/Polytonic/Chlorine)
[![Coverage Status](http://img.shields.io/coveralls/Polytonic/Chlorine.svg?style=flat-square)](https://coveralls.io/r/Polytonic/Chlorine)
[![OpenCL Version](http://img.shields.io/badge/OpenCL-1.2%2B-brightgreen.svg?style=flat-square)](https://www.khronos.org/opencl/)

## Summary
Chlorine is a simple way to interact with [OpenCL](https://www.khronos.org/opencl/) compatible devices. Chlorine allows you to write code that runs on graphics processing units without ever touching the OpenCL API, leaving you free to write code that matters: kernels that process data.

## Getting Started
Chlorine is distributed as a single header: [chlorine.hpp](https://github.com/Polytonic/Chlorine/blob/master/chlorine/chlorine.hpp). You'll also need any version of the [OpenCL C++ Bindings](http://www.khronos.org/registry/cl/api/1.2/cl.hpp) and a compiler with `C++11` support. An example of how to use Chlorine is shown below. You can also read a more detailed [walkthrough](https://github.com/Polytonic/Chlorine/tree/master/examples/swap) if you prefer.

**main.cpp**
```c++
// Include the Chlorine Header
#include "chlorine.hpp"
int main(int argc, char * argv[])
{
    // Create Some Data
    std::vector<float> spam(10, 3.1415f);
    std::vector<float> eggs(10, 2.7182f);

    // Initialize a Chlorine Worker
    ch::Worker worker("swap.cl");

    // Call the Swap Function in the Given Kernel
    auto event = worker.call("swap", spam, eggs);

    // Host Containers Are Automatically Updated
    std::cout << "Spam: " << spam[0] << "\n"; // 2.7182
    std::cout << "Eggs: " << eggs[0] << "\n"; // 3.1415

    // Print Some Profiling Data
    std::cout << "Elapsed Time: " << ch::elapsed(event) << "ns\n";
}
```
**swap.cl**
```c
__kernel void swap(__global float * spam, __global float * eggs)
{
    unsigned int i = get_global_id(0);
    float swap = spam[i];
    spam[i] = eggs[i];
    eggs[i] = swap;
}
```

Chlorine uses the [cmake](http://www.cmake.org/) build system. If you're looking to compile the examples or contribute to Chlorine, you'll need to do the following:

```
# Create the Out-of-Source Builds Folder
mkdir -p build && cd build
```

Now generate a project file or makefile for your platform. If you want to use a particular IDE, make sure it is installed; don't forget to set the Start-Up Project in Visual Studio or the Target in Xcode.

```
# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 14" ..
cmake -G "Visual Studio 14 Win64" ..
...

```

## Documentation
The core philosophy in Chlorine is that you should *work with your data*, instead of spending time fighting an API. To that end, Chlorine acts as a lightweight interface to OpenCL, automatically mapping arguments passed on the host to kernel functions running on a device. The underlying implementation uses variadic templating to accept any number of arguments of any type, allowing you to mix scalar and vector types as needed. The following types are supported:

- [Arithmetic Scalar Types](http://www.cplusplus.com/reference/type_traits/is_arithmetic/)
- [OpenCL Vector Types](https://www.khronos.org/registry/cl/sdk/1.2/docs/man/xhtml/vectorDataTypes.html)
- [C-Style Arrays](http://www.cplusplus.com/doc/tutorial/arrays/)
- [STL Arrays](http://www.cplusplus.com/reference/array/array/)
- [STL Valarrays](http://www.cplusplus.com/reference/valarray/)
- [STL Vectors](http://www.cplusplus.com/reference/vector/vector/)

Note that kernels may not automatically perform type promotion. When working with floating point numbers, be sure to use the appropriate literal. For instance, `3.14` vs. `3.14f`.

For convenience, Chlorine also provides a simple version of `clinfo`, allowing you to print basic information about OpenCL devices on your computer. You can build it by invoking `make`, and optionally, `make install` to copy it to your system.

## License
>The MIT License (MIT)

>Copyright (c) 2014 Kevin Fung

>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
