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
    std::vector<std::string> split(const std::string & s, char delim);
    int print_exception_string(cl::Error exception);

    // OpenCL Containers
    std::vector<cl::Platform> platforms;
    std::vector<cl::Device> devices;

    // Chlorine Configuration
    std::vector<std::string> extensions;
    const unsigned int width = 35;
    static struct option opts[] =
    {
        { "help", no_argument, NULL, 'h' },
        {  NULL , 0          , NULL,  0  },
    };
}

// Local Dependencies
#include "utilities.hpp"
#include "clinfo.hpp"
#include "error.hpp"

#endif
