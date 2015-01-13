// Include Testsuite Dependencies
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "test_suite.hpp"

/*
    We define repeated test cases since Catch doesn't support templated tests.
    Refer to https://github.com/philsquared/Catch/issues/46 for details.
 */

// Chlorine Integers Test
TEST_CASE("Chlorine Adds       Integers", "[int, add]") { test<int>("add"); }
TEST_CASE("Chlorine Subtracts  Integers", "[int, sub]") { test<int>("sub"); }
TEST_CASE("Chlorine Multiplies Integers", "[int, mul]") { test<int>("mul"); }


// swap, add, sub, mul, exp, pow?
/* for every container, test every type mapping
    bool
    unsigned char
    char
    unsigned short
    short
    unsigned int
    int
    unsigned long
    long
    half
    float
 */
