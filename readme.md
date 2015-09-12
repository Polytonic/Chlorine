# [Chlorine](http://polytonic.github.io/Chlorine/)
[![Build Status](http://img.shields.io/travis/Polytonic/Chlorine/master.svg?style=flat-square)](https://travis-ci.org/Polytonic/Chlorine)
[![Coverage Status](http://img.shields.io/coveralls/Polytonic/Chlorine.svg?style=flat-square)](https://coveralls.io/r/Polytonic/Chlorine)
[![OpenCL Version](http://img.shields.io/badge/OpenCL-1.2%2B-brightgreen.svg?style=flat-square)](https://www.khronos.org/opencl/)

## Summary
Chlorine is the easiest way to interact with [OpenCL](https://www.khronos.org/opencl/) compatible devices. Chlorine allows you to write cross-platform code that runs on GPUs, without ever touching the complicated OpenCL API, leaving you free to write code that matters: kernels that process your data.

## Getting Started
Chlorine is composed of just two headers: [chlorine.hpp](https://github.com/Polytonic/Chlorine/blob/master/chlorine/include/chlorine.hpp), and its dependency, the [OpenCL C++ Bindings](http://www.khronos.org/registry/cl/api/1.2/cl.hpp). To integrate Chlorine into your own project, [install OpenCL](), then add `chlorine/include` to your include paths. Chlorine also requires a compiler with `C++11` support. An example of how to use Chlorine is below. You can also read a more detailed [walkthrough](https://github.com/Polytonic/Chlorine/tree/master/examples/swap) if you prefer.

**main.cpp**
```c++
std::vector<float> data(10, 3.1415f);        // Create Some Sample Data
ch::Worker worker("square.cl");              // Initialize a Chlorine Worker
auto event = worker.call("square", data);    // Call Kernel Square Function
std::cout << "Data: " << data[0] << "\n";    // Prints 9.8696

// Print Some Profiling Data
std::cout << "Elapsed Time: " << ch::elapsed(event) << "ns\n";
```
**square.cl**
```c
__kernel void square(__global float * data) {
    unsigned int i = get_global_id(0);
    data[i] = data[i] * data[i];
}
```

Want to get started right away? If you're looking to compile the examples or play around in the sandbox project, follow these steps! Chlorine uses the [cmake](http://www.cmake.org/) build system, which is used to generate platform-specific makefiles or project files.

```bash
git clone https://github.com/Polytonic/Chlorine
cd Chlorine
cd build
```

Now generate a project file or makefile for your platform. If you want to use a particular IDE, make sure it is installed; don't forget to set the Start-Up Project in Visual Studio or the Target in Xcode.

```bash
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

For convenience, Chlorine also provides a simple version of `clinfo`, allowing you to print basic information about OpenCL devices on your computer. You can build it using `cmake`.

documentation blocks are available above method definitions. The class declaration is useful as a quick API reference. If you need a more sophisticated viewer, use doxygen to generate the HTML representation of the annotations.

## License
>The MIT License (MIT)

>Copyright (c) 2015 Kevin Fung

>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
