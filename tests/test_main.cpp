// Include Testsuite Dependencies
#define __CL_ENABLE_EXCEPTIONS
#define CATCH_CONFIG_MAIN
#include "test_suite.hpp"

/*
    We define repeated test cases since Catch doesn't support templated tests.
    Refer to https://github.com/philsquared/Catch/issues/46 for details.
 */

// Chlorine Integer Arrays Test
TEST_CASE("Adds       Integers", "[int][add]") { test<int>("integers", "add"); }
TEST_CASE("Subtracts  Integers", "[int][sub]") { test<int>("integers", "sub"); }
TEST_CASE("Multiplies Integers", "[int][mul]") { test<int>("integers", "mul"); }

// Chlorine Float Arrays Test
TEST_CASE("Adds       Floats", "[float][add]") { test<float>("floats", "add"); }
TEST_CASE("Subtracts  Floats", "[float][sub]") { test<float>("floats", "sub"); }
TEST_CASE("Multiplies Floats", "[float][mul]") { test<float>("floats", "mul"); }

// Chlorine Scalar Primitives Test
TEST_CASE("Scalars", "[arithmetic][scalars]")
{
    // Create a Worker and Load the Correct Types Kernel
    ch::Worker worker("kernels/test_scalars.cl");
    srand(static_cast<unsigned>(time(0)));
    size_t const n = 10;

    SECTION("Scalar Integers")
    {
        INFO("Testing Scalar Function: ifill");
        int b = rand();
        std::vector<int> a(n);
        worker.call("ifill", a, b);
        for (unsigned int i = 0; i < a.size(); i++)
            CHECK(a[i] == b);
    }

    SECTION("Scalar Floats")
    {
        INFO("Testing Scalar Function: ffill");
        float b = rand() / static_cast<float>(RAND_MAX) * 100.0f;
        std::vector<float> a(n);
        worker.call("ffill", a, b);
        for (unsigned int i = 0; i < a.size(); i++)
            CHECK(a[i] == b);
    }
}

// Chlorine Vector Primitives Test
TEST_CASE("Vectors", "[arithmetic][vectors]")
{
    // Create a Worker and Load the Correct Types Kernel
    ch::Worker worker("kernels/test_vectors.cl");
    size_t const n = 10;

    SECTION("Vector Integers")
    {
        INFO("Testing Vector Function: ifill");
        std::vector<cl_int4> a(n);
        worker.call("ifill", a);
        for (unsigned int i = 0; i < a.size(); i++)
            for (unsigned int j = 0; j < 4; j++)
                CHECK(a[i].s[j] == j);
    }

    SECTION("Vector Floats")
    {
        INFO("Testing Vector Function: ffill");
        std::vector<cl_float4> a(n);
        worker.call("ffill", a);
        for (unsigned int i = 0; i < a.size(); i++)
            for (unsigned int j = 0; j < 4; j++)
                CHECK(a[i].s[j] == static_cast<float>(j));
    }
}

// Test Chlorine Worker Helpers
TEST_CASE("Helpers", "[helpers]")
{
    SECTION("ch::elapsed() Returns an Elapsed Time")
    {
        ch::Worker worker("kernels/test_helpers.cl");
        std::vector<int> a(100, 100);
        auto event = worker.call("fill", a);
        for (unsigned int i = 0; i < a.size(); i++)
            CHECK(a[i] == 1);
        CHECK(ch::elapsed(event) > 0);
    }

    SECTION("ch::read() Returns File Contents")
    {
        // Read Kernel Source
        std::string kernel = ch::read("kernels/test_helpers.cl");

        // Define String Literal to Match
        std::string match =
            "// Test the Kernel Read Function\n"
            "__kernel void fill(__global int * a)\n"
            "{\n"
            "    unsigned int i = get_global_id(0);\n"
            "    a[i] = 1;\n"
            "}\n";

        // Assert Kernel Source is Equivalent
        CHECK(kernel == match);
    }

    SECTION("Operator >> Accepts Kernel Strings")
    {
        ch::Worker worker;
        REQUIRE_NOTHROW(worker >> ch::read("kernels/test_helpers.cl"));
    }

    SECTION("Operator << Prints the Build Log")
    {
        ch::Worker worker;
        REQUIRE_THROWS(worker >> ch::read("kernels/test_operators.cl"));
        INFO("Build Log" << worker);
    }
}
