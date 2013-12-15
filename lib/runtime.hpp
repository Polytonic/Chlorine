#ifndef CHLORINE_RUNTIME
#define CHLORINE_RUNTIME

namespace ch
{
    template <typename Float, typename FloatN>
    void execute()
    {
        std::cout << sizeof(Float)  << std::endl;
        std::cout << sizeof(FloatN) << std::endl;
    }
}

// Template Typename Float, FloatN
// Load Data from File
// Save Data to Arrays
// Allocate Buffers and Work Dims
// Set Kernel Arguments
// Pass Extra Arguments
// Execute Kernel on CommandQueue
// Should Run this in Background
// Write Buffer Data to File
// Clean Up and Exit
// Print Some Diagnostic Data

#endif