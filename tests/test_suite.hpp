// Local Dependencies
#include "chlorine.hpp"
#include <catch.hpp>

// Standard Library Headers
#include <memory>
#include <numeric>
#include <typeinfo>
#include <valarray>

template<typename T>
T test_ops(std::string const & instr, T a, T b)
{
         if (instr == "add") { return a + b; }
    else if (instr == "sub") { return a - b; }
    else if (instr == "mul") { return a * b; }
    else return -1;
}

// Parameterize Tests Across Types
template<typename T>
void test(std::string const & type, std::string const & instr, T val = 1)
{
    // Create a Worker and Load the Correct Types Kernel
    INFO("Testing Function: " << instr << typeid(T).name());
    ch::Worker worker; worker >> ch::read("kernels/test_" + type + ".cl");

    // Define Two Vectors of Test Data
    size_t const n = 10;
    std::vector<T> a(n, val);
    std::iota(a.begin(), a.end(), val);
    std::vector<T> b(a);

    SECTION("Worker Accepts C-Style Arrays")
    {
        T raw_array[n];
        worker.call(instr, a, b, raw_array);
        for (unsigned int i = 0; i < n; i++)
            CHECK(test_ops(instr, a[i], b[i]) == raw_array[i]);
    }

    SECTION("Worker Accepts STL Arrays")
    {
        std::array<T, n> stl_array;
        worker.call(instr, a, b, stl_array);
        for (unsigned int i = 0; i < n; i++)
            CHECK(test_ops(instr, a[i], b[i]) == stl_array[i]);
    }

    SECTION("Worker Accepts STL Valarrays")
    {
        std::valarray<T> stl_valarray(n);
        worker.call(instr, a, b, stl_valarray);
        for (unsigned int i = 0; i < n; i++)
            CHECK(test_ops(instr, a[i], b[i]) == stl_valarray[i]);
    }

    SECTION("Worker Accepts STL Vectors")
    {
        std::vector<T> stl_vector(n);
        worker.call(instr, a, b, stl_vector);
        for (unsigned int i = 0; i < n; i++)
            CHECK(test_ops(instr, a[i], b[i]) == stl_vector[i]);
    }
}
