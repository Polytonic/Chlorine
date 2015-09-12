# OpenCL Installation Instructions

### Windows

**AMD:** Install the [AMD APP SDK](http://developer.amd.com/tools-and-sdks/opencl-zone/amd-accelerated-parallel-processing-app-sdk/).

**Nvidia:** Install the [CUDA SDK](https://developer.nvidia.com/cuda-downloads).

### Mac OSX

OpenCL is part of the Apple Developer Tools. You can access the OpenCL runtime by installing Xcode, or by installing the Xcode Command Line Tools via `xcode-select --install` and following the prompts.

### Linux

This one I'm a bit more fuzzy on.

**Nvidia** support should be available under most package managers, e.g. `sudo apt-get install nvidia-opencl-dev`.

**AMD** should work with `sudo apt-get install fglrx-dev`, but your mileage may vary.

You may also need to `sudo apt-get install opencl-headers`. Substitute your distro's package manager where appropriate.
