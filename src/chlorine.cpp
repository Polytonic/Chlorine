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


        // Create a Command Queue from Selected Device
        // Should Parse Arguments At Some Point
        ch::Queue = cl::CommandQueue(ch::Context, ch::Device,
                    ch::profiling ? CL_QUEUE_PROFILING_ENABLE : 0);


        std::cout << "Hello World";


    } catch (cl::Error exception) {
        ch::print_exception_string(exception);
        std::cout << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
