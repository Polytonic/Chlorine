// Standard Library Headers
#include <iostream>

// Platform Specific Headers
#ifdef __APPLE__
#include <OpenCL/OpenCL.h>
#else
#include <CL/OpenCL.h>
#endif


int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

