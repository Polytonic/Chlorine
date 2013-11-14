// Local Dependencies
#include "chlorine.hpp"

int main(int argc, const char * argv[])
{
    try {

        // Display OpenCL Implementation Information
        cl::Platform::get(& ch::platforms);
        if (ch::platforms.size() > 0)
            std::cout << std::string(80,'-')
                      << std::endl;

        for (unsigned int i = 0; i < ch::platforms.size(); i++)
        {
            // Query Platform Information
            ch::get_platform_info(ch::platforms[i]);
            std::cout << std::endl;

            // Query Device Information
            ch::platforms[i].getDevices(CL_DEVICE_TYPE_ALL, & ch::devices);
            for (unsigned int j = 0; j < ch::devices.size(); j++)
            {
                ch::get_device_info(ch::devices[j]);
                std::cout << std::endl;
            }   std::cout << std::string(80,'-') << std::endl;
        }

    } catch (cl::Error exception) {
        ch::print_exception_string(exception);
        std::cout << argc << *argv;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
