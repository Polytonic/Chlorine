// Local Dependencies
#include "chlorine.hpp"
int main(int argc, const char * argv[])
{
    try {
        // Load OpenCL Platform and Devices
        cl::Platform::get(& ch::platforms);
        for (unsigned int i = 0; i < ch::platforms.size(); i++)
            ch::platforms[i].getDevices(CL_DEVICE_TYPE_ALL, & ch::devices);

        ch::Device = ch::devices[0];

        // Parse the Kernel File and Generate Command Queues
        load_kernels("/Users/Dropbox/Documents/Arsenal/Chlorine/src/kernel.cl");

        std::cout << "Hello World";


    } catch (cl::Error exception) {
        ch::print_exception_string(exception);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
