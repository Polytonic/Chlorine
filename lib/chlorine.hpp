#ifndef CHLORINE_MAIN
#define CHLORINE_MAIN

// Enable Extensions and Exceptions
#define __CL_ENABLE_EXTENSIONS
#define __CL_ENABLE_EXCEPTIONS

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

    // OpenCL Containers
    std::vector<cl::Platform> platforms;

    // Diagnostic Information
    std::vector<std::string> extensions;

    // Output Formatting
    const unsigned int width = 25;
}

// Create Namespace Alias
namespace chlorine = ch;

#endif
