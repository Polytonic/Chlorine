// Include STL Containers
#include <valarray>

// Include Testsuite Dependencies
#define CATCH_CONFIG_MAIN
#include "chlorine.hpp"
#include "catch.hpp"

// Load the Container Test Sections
TEST_CASE("Workers are Compatible With Containers", "[containers]") {
    #include "containers.hpp"
}

// Load the Helper Test Sections
TEST_CASE("Test Helper Functions", "[helpers]") {
    #include "helpers.hpp"
}

// Load the Integer Test Sections
TEST_CASE("Test Integer Compatibility", "[ints]") {
    #include "integers.hpp"
}

// Load the Float Test Sections
TEST_CASE("Test Float Compatibility", "[floats]") {
    #include "floats.hpp"
}
