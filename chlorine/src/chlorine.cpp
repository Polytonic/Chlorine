// Include the Chlorine Header
#include "chlorine.hpp"

// Define an OpenCL Kernel
static const char* kernel =
    "__kernel void swap(__global float * spam, __global float * eggs)"
    "{"
    "    unsigned int i = get_global_id(0);"
    "    float swap = spam[i];"
    "    spam[i] = eggs[i];"
    "    eggs[i] = swap;"
    "}"
;

// Slightly Modified Sample Code from Readme
int main(int argc, char * argv[])
{
    // Create Some Data
    std::vector<float> spam(10, 3.1415f);
    std::vector<float> eggs(10, 2.7182f);

    // Initialize a Chlorine Worker
    ch::Worker worker;

    // Build the OpenCL Kernel
    worker.build_kernel(kernel);

    // Call the Swap Function in the Given Kernel
    auto event = worker.call("swap", spam, eggs);

    // Host Containers Are Automatically Updated
    std::cout << "Spam: " << spam[0] << "\n"; // 2.7182
    std::cout << "Eggs: " << eggs[0] << "\n"; // 3.1415

    // Print Some Profiling Data
    std::cout << "Elapsed Time: " << ch::elapsed(event) << "ns\n";
}
