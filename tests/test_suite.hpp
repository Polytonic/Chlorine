// Local Dependencies
#include "chlorine.hpp"

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
void test(std::string const & instr, T val = 1)
{
    // Create a Worker and Load the Correct Types Kernel
    std::cerr << "Testing Function: " << instr << typeid(T).name() << "\n";
    ch::Worker worker; worker >> ch::read("tests/test_integers.cl");

    // Define Two Vectors of Test Data
    size_t const n = 5;
    std::vector<T> a(n, val);
    std::iota(a.begin(), a.end(), val);
    std::vector<T> b(a);

    SECTION("Worker Accepts C-Style Arrays")
    {
        T raw_array[n];
        worker.call(instr, a, b, raw_array);
        for (unsigned int i = 0; i < n; i++)
            CHECK(raw_array[i] == test_ops(instr, a[i], b[i]));
        std::cerr << std::endl;
    }

    // SECTION("Worker Accepts Heap Allocated Arrays")
    // {
    //     T * mem_array = new T[n];
    //     worker.call(instr, a, b, mem_array);
    //     for (unsigned int i = 0; i < n; i++)
    //         CHECK(mem_array[i] == test_ops(instr, a[i], b[i]));
    //     delete [] mem_array;
    // }

    SECTION("Worker Accepts STL Arrays")
    {
        std::array<T, n> stl_array;
        worker.call(instr, a, b, stl_array);
        for (unsigned int i = 0; i < n; i++)
            CHECK(stl_array[i] == test_ops(instr, a[i], b[i]));
        std::cerr << std::endl;
    }

    SECTION("Worker Accepts STL Valarrays")
    {
        std::valarray<T> stl_valarray(0, n);
        worker.call(instr, a, b, stl_valarray);
        for (unsigned int i = 0; i < n; i++)
            CHECK(stl_valarray[i] == test_ops(instr, a[i], b[i]));
        std::cerr << std::endl;
    }

    SECTION("Worker Accepts STL Vectors")
    {
        std::vector<T> stl_vector(n);
        worker.call(instr, a, b, stl_vector);
        for (unsigned int i = 0; i < n; i++)
            CHECK(stl_vector[i] == test_ops(instr, a[i], b[i]));
        std::cerr << std::endl;
    }

    // SECTION("Worker Accepts STL Smart-Pointers")
    // {
    //     std::
    // }
}
