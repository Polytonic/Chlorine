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
        
    } catch (cl::Error exception) {
        chlorine::print_exception_string(exception);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
