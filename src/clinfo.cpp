// Standard Library Headers
#include <iostream>

// Local Dependencies
#include "clinfo.hpp"

int main(int argc, const char * argv[])
{
    std::cout << argc << std::endl;
    std::cout << sizeof(*argv) << std::endl;
    // insert code here...
    std::cout << "Hello, CL!\n";
    return 0;
}
