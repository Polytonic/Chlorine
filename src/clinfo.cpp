// Standard Library Headers
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

// Local Dependencies
#include "utilities.hpp"
#include "chlorine.hpp"
#include "clinfo.hpp"
#include "error.hpp"

int main(int argc, const char * argv[])
{
    try {

        cl::Platform::get(& ch::platforms);
        ch::get_platform_info(ch::platforms[0]);
        std::cout << std::endl;

        ch::platforms[0].getDevices(CL_DEVICE_TYPE_ALL, & ch::devices);
        ch::get_device_info(ch::devices[0]);
        std::cout << std::endl;
        
    } catch (cl::Error exception) {
        chlorine::print_exception_string(exception);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
