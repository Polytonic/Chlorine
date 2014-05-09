#define CATCH_CONFIG_MAIN
#include "chlorine.hpp"
#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE("Worker Default Constructor") {

    ch::Worker worker("tests/kernels/default.cl");

    CHECK( Factorial(1) == 1);
    CHECK( Factorial(2) == 2);
    CHECK( Factorial(3) == 6);
}
