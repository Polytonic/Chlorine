// Local Dependencies
#include "chlorine.hpp"

int main(int argc, char * argv[])
{
    try {

        // Load OpenCL Platform and Devices
        cl::Platform::get(& ch::platforms);
        for (unsigned int i = 0; i < ch::platforms.size(); i++)
            ch::platforms[i].getDevices(CL_DEVICE_TYPE_ALL, & ch::devices);

        ch::Device = ch::devices[0];

        // Parse the Kernel File and Generate Command Queues
        ch::parse_arguments(argc, argv);
        ch::load_kernels("/Users/Dropbox/Documents/Arsenal/Chlorine/src/kernel.cl");

        // Create a Command Queue from Selected Device
        // Should Parse Arguments At Some Point
        ch::Queue = cl::CommandQueue(ch::Context, ch::Device,
                    ch::profiling ? CL_QUEUE_PROFILING_ENABLE : 0);

        // 32-bit Floating Point Precision
        if (ch::precision == 4) {
        switch (ch::vec_width)  {
            case 1:  ch::execute<cl_float, cl_float>();   break;
            case 2:  ch::execute<cl_float, cl_float2>();  break;
            case 3:  ch::execute<cl_float, cl_float3>();  break;
            case 4:  ch::execute<cl_float, cl_float4>();  break;
            case 8:  ch::execute<cl_float, cl_float8>();  break;
            case 16: ch::execute<cl_float, cl_float16>(); break;
            default: std::cerr << "Invalid Vector Width"; break;
        }}

        // 64-bit Floating Point Precision
        else if (ch::precision == 8) {
        switch  (ch::vec_width)      {
            case 1:  ch::execute<cl_double, cl_double>();   break;
            case 2:  ch::execute<cl_double, cl_double2>();  break;
            case 3:  ch::execute<cl_double, cl_double3>();  break;
            case 4:  ch::execute<cl_double, cl_double4>();  break;
            case 8:  ch::execute<cl_double, cl_double8>();  break;
            case 16: ch::execute<cl_double, cl_double16>(); break;
            default: std::cerr << "Invalid Vector Width";   break;
        }}

    } catch (cl::Error exception) {
        ch::print_exception_string(exception);
        std::cout << std::endl;
        return EXIT_FAILURE;
    }   return EXIT_SUCCESS;
}
