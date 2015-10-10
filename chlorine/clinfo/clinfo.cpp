// Include OpenCL C++ Bindings
#include "cl.hpp"

// Standard Library Dependencies
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// Splits a String by Whitespace Delimiter
std::vector<std::string> tokenize(std::string const & str)
{
    std::string buffer = "";
    std::stringstream ss(str);
    std::vector<std::string> tokens;
    while (ss >> buffer)
        tokens.push_back(buffer);
    return tokens;
}

// Prints Basic OpenCL Runtime Information
int main(int argc, char * argv[])
{
    // Print a Section Break
    for(unsigned int i = 0; i < 80; i++)
        printf("=");
        printf("\n");

    // Enumerate Platform Information
    std::vector<cl::Platform> platforms;
    cl::Platform::get(& platforms);
    for (auto &platform : platforms)
    {
        printf("Platform: %s %s\nVendor: %s (%s)\n",
            platform.getInfo<CL_PLATFORM_NAME>().c_str(),
            platform.getInfo<CL_PLATFORM_VERSION>().c_str(),
            platform.getInfo<CL_PLATFORM_VENDOR>().c_str(),
            platform.getInfo<CL_PLATFORM_PROFILE>().c_str());

        printf("Supported Extensions:\n\n");
        for (auto &extension : tokenize(platform.getInfo<CL_PLATFORM_EXTENSIONS>()))
            printf("\t%s\n", extension.c_str());
            printf("\n");

        printf("Available Devices:\n\n");
        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, & devices);
        for (auto &device : devices)
        {
            printf("\tDevice: %s %s\n",
                   device.getInfo<CL_DEVICE_VENDOR>().c_str(),
                   device.getInfo<CL_DEVICE_NAME>().c_str());

            printf("\tType: ");
            switch (device.getInfo<CL_DEVICE_TYPE>())
            {
                case CL_DEVICE_TYPE_CPU: printf("CPU");                 break;
                case CL_DEVICE_TYPE_GPU: printf("GPU");                 break;
                case CL_DEVICE_TYPE_ACCELERATOR: printf("Accelerator"); break;
                default: printf("Unknown");
            }   printf(" (%d-bit @ %d MHz)\n",
                    device.getInfo<CL_DEVICE_ADDRESS_BITS>(),
                    device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>());

            printf("\tSupported Extensions:\n\n");
            for (auto &extension : tokenize(device.getInfo<CL_DEVICE_EXTENSIONS>()))
                printf("\t\t%s\n", extension.c_str());
                printf("\n");
        }

        // Print a Section Break
        for(unsigned int i = 0; i < 80; i++)
            printf("=");
            printf("\n");
    }

    return EXIT_SUCCESS;
}
