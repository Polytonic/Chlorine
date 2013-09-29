// Standard Library Headers
#include <iostream>

// Local Dependencies
#include "chlorine.hpp"
#include "error.hpp"

int main(int argc, const char * argv[])
{
    std::cout << argc << std::endl;
    std::cout << sizeof(*argv) << std::endl;
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
