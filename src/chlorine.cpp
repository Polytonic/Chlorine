// Local Dependencies
#include "chlorine.hpp"

int main(int argc, char * argv[])
{
    try {

        ch::parse_arguments(argc, argv);

    } catch (cl::Error exception) {
        ch::print_exception_string(exception);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
