// Local Dependencies
#include "chlorine.hpp"

int main(int argc, const char * argv[])
{
    try {

        std::cout << argc << std::endl;
        std::cout << sizeof(*argv) << std::endl;

    } catch (cl::Error exception) {
        ch::print_exception_string(exception);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
