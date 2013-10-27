#ifndef CHLORINE_CLINFO
#define CHLORINE_CLINFO

#include "chlorine.hpp"

namespace ch
{
    void get_platform_info(cl::Platform platform)
    {
        // Print Platform Information
        std::cout << std::setw(ch::width) << std::left << "Platform Name:"
                  << platform.getInfo<CL_PLATFORM_NAME>() << std::endl
                  << std::setw(ch::width) << std::left << "Platform Profile:"
                  << platform.getInfo<CL_PLATFORM_PROFILE>()    << std::endl
                  << std::setw(ch::width) << std::left << "Platform Vendor:"
                  << platform.getInfo<CL_PLATFORM_VENDOR>()     << std::endl
                  << std::setw(ch::width) << std::left << "Platform Version:"
                  << platform.getInfo<CL_PLATFORM_VERSION>()    << std::endl;

        // Print Supported Platform Extensions
        std::cout << "Platform Extensions:\n" << std::endl;
        ch::extensions = ch::split(platform.getInfo<CL_PLATFORM_EXTENSIONS>());
        for (unsigned int i = 0; i < ch::extensions.size(); i++)
            std::cout << "\t" << ch::extensions[i] << std::endl;
    }
}

#endif
