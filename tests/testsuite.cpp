// Include Extra STL Containers
#include <valarray>
#include <numeric>

// Include Testsuite Dependencies
#define CATCH_CONFIG_MAIN
#include "chlorine.hpp"
#include "catch.hpp"

template<typename T>
void test(T val)
{
    ch::Worker worker;
    worker >> ch::read("tests/kernels/integers.cl");

    // Define Two Vectors of Test Data
    size_t const n = 10;
    std::vector<T> a(n, val);
    std::iota(a.begin(), a.end(), val);
    std::vector<T> b(a);

                   T     raw_array [n];
    std::array    <T, n> stl_array;
    std::valarray <T>    stl_valarray(0, n);
    std::vector   <T>    stl_vector(n);

    worker.call("add", a, b, raw_array);
    // worker.call("add", a, b, stl_array);
    // worker.call("add", a, b, stl_valarray);
    // worker.call("add", a, b, stl_vector);

    for (unsigned int i = 0; i < n; i++)
    {
        CHECK(raw_array[i]    == a[i] + b[i]);
        CHECK(stl_array[i]    == a[i] + b[i]);
        CHECK(stl_valarray[i] == a[i] + b[i]);
        CHECK(stl_vector[i]   == a[i] + b[i]);
    }
}
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

    C Array
    STL Array
    STL Valarray
    STL Vector



 */

// Load the Container Test Sections
TEST_CASE("Workers are Compatible With Containers", "[containers]") {
    #include "containers.hpp"
}

// // Load the Helper Test Sections
// TEST_CASE("Test Helper Functions", "[helpers]") {
//     #include "helpers.hpp"
// }

// // Load the Integer Test Sections
// TEST_CASE("Test Integer Compatibility", "[ints]") {
//     #include "integers.hpp"
// }

// // Load the Float Test Sections
// TEST_CASE("Test Float Compatibility", "[floats]") {
//     #include "floats.hpp"
// }
