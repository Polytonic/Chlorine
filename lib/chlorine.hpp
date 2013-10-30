#ifndef CHLORINE_MAIN
#define CHLORINE_MAIN

// Enable Extensions and Exceptions
#define __CL_ENABLE_EXTENSIONS
#define __CL_ENABLE_EXCEPTIONS

// Standard Library Headers
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

// UNIX Header Includes
#include <unistd.h>
#include <getopt.h>

// Include OpenCL C++ Bindings
#pragma GCC diagnostic push
#pragma GCC system_header
#include "cl.hpp"
#pragma GCC diagnostic pop

// Create Chlorine Namespace
namespace ch
{
    // Function Prototypes
    void get_platform_info(cl::Platform platform);
    void get_device_info(cl::Device device);

    // OpenCL Containers
    std::vector<cl::Platform> platforms;
    std::vector<cl::Device> devices;

    // Diagnostic Information
    std::vector<std::string> extensions;

    // Output Formatting
    const unsigned int width = 35;
}

// Local Dependencies
#include "utilities.hpp"
#include "clinfo.hpp"
#include "error.hpp"

#endif
