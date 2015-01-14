# [Chlorine](http://polytonic.github.io/Chlorine/)
[![Build Status](http://img.shields.io/travis/Polytonic/Chlorine.svg?style=flat-square)](https://travis-ci.org/Polytonic/Chlorine)
[![Coverage Status](http://img.shields.io/coveralls/Polytonic/Chlorine.svg?style=flat-square)](https://coveralls.io/r/Polytonic/Chlorine)
[![OpenCL Version](http://img.shields.io/badge/OpenCL-1.2%2B-brightgreen.svg?style=flat-square)](https://www.khronos.org/opencl/)

## Summary
Chlorine is a simple way to interact with [OpenCL](https://www.khronos.org/opencl/) compatible devices. You can rapidly *prototype* parallel processing on graphics processing units using a generic worker implementation that abstracts away much of the boilerplate involved with writing OpenCL applications.

## Getting Started
Chlorine is distributed as a single header: [chlorine.hpp](https://github.com/Polytonic/Chlorine/blob/master/chlorine/chlorine.hpp). You'll also need any version of the [OpenCL C++ Bindings](http://www.khronos.org/registry/cl/api/1.2/cl.hpp) and a compiler with `C++11` support. Here is a short example:

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
    worker.call("swap", spam, eggs);

    // Host Containers Are Automatically Updated
    std::cout << "Spam: " << spam[0] << "\n"; // 2.7182
    std::cout << "Eggs: " << eggs[0] << "\n"; // 3.1415
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

You can build all of the samples by invoking `make examples`, or you can examine and build individual samples in the [examples](https://github.com/Polytonic/Chlorine/tree/master/examples) subdirectory.

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
