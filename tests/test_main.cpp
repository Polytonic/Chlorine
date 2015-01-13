// Include Testsuite Dependencies
#define CATCH_CONFIG_MAIN
#include "test_suite.hpp"

// Verifies the Default Case for Code Coverage Purposes
TEST_CASE("Test Operations Selector, [dummy, ops]")
{
    CHECK(test_ops<int>("add", 1, 2) ==  3);
    CHECK(test_ops<int>("___", 0, 0) == -1);
}

/*
    We define repeated test cases since Catch doesn't support templated tests.
    Refer to https://github.com/philsquared/Catch/issues/46 for details.
 */

// Chlorine Integer Arrays Test
TEST_CASE("Adds       Integers", "[int, add]") { test<int>("integers", "add"); }
TEST_CASE("Subtracts  Integers", "[int, sub]") { test<int>("integers", "sub"); }
TEST_CASE("Multiplies Integers", "[int, mul]") { test<int>("integers", "mul"); }

// Chlorine Float Arrays Test
TEST_CASE("Adds       Floats", "[float, add]") { test<float>("floats", "add"); }
TEST_CASE("Subtracts  Floats", "[float, sub]") { test<float>("floats", "sub"); }
TEST_CASE("Multiplies Floats", "[float, mul]") { test<float>("floats", "mul"); }
