#ifndef CHLORINE_MAIN
#define CHLORINE_MAIN

// Platform Specific Headers
#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/opencl.h>
#endif

// Include OpenCL C++ Bindings
#pragma GCC diagnostic push
#pragma GCC system_header
#include "cl.hpp"
#pragma GCC diagnostic pop

// Create Chlorine Namespace
namespace chlorine {}

// Create Namespace Alias
namespace ch = chlorine;

#endif
