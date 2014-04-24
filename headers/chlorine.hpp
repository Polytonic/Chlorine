// Chlorine Main Header
#ifndef CHLORINE_MAIN
#define CHLORINE_MAIN

// Enable Extensions and Exceptions
#define __CL_ENABLE_EXTENSIONS
#define __CL_ENABLE_EXCEPTIONS

// Include OpenCL C++ Bindings
#pragma GCC diagnostic push
#pragma GCC system_header
#include "vendor/cl.hpp"
#pragma GCC diagnostic pop

// Standard Library Headers
#include <iostream>
#include <fstream>
#include <map>
#include <valarray>

// POSIX Headers

// Local Headers
#include "include/worker.hpp"

#endif
