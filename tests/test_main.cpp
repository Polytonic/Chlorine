// Include Testsuite Dependencies
#define CATCH_CONFIG_MAIN
#include "test_suite.hpp"

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

// Chlorine Scalar Primitives Test
TEST_CASE("Primitives", "[primitives]")
{
    // Create a Worker and Load the Correct Types Kernel
    ch::Worker worker; worker >> ch::read("tests/test_primitives.cl");
    srand(static_cast<unsigned>(time(0)));
    size_t const n = 5;

    SECTION("Scalar Integers")
    {
        std::cerr << "Testing Scalar Function: ifill\n";
        int b = rand();
        std::vector<int> a(n);
        worker.call("ifill", a, b);
        for (unsigned int i = 0; i < a.size(); i++)
            CHECK(a[i] == b);
        std::cerr << std::endl;
    }

    SECTION("Scalar Floats")
    {
        std::cerr << "Testing Scalar Function: ffill\n";
        float b = rand() / static_cast<float>(RAND_MAX) * 100.0f;
        std::vector<float> a(n);
        worker.call("ffill", a, b);
        for (unsigned int i = 0; i < a.size(); i++)
            CHECK(a[i] == b);
        std::cerr << std::endl;
    }
}
