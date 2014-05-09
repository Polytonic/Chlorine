#include "chlorine.hpp"
#include <valarray>
#include <fstream>

int main()
{
    // Test Vector of Ints
    std::vector<int>    spam  (10, 1);
    std::vector<int>    ham   (10, 2);

    std::vector<float>  eggs  (10, 2.7182f);
    std::valarray<float>  bacon (3.1415f, 10); // valarray constructor is backwards

    std::array<int, 10> spinach = {{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 }};
    int cheese[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    ch::Worker busybot("tests/kernels/default.cl");
    busybot >> ch::read("tests/kernels/default.cl");
    busybot.execute("add", spam, ham, 1, eggs, bacon, 1.0f, spinach, cheese);

    std::cout << spam[0] << std::endl;  // Should Print 4
    std::cout << eggs[0] << std::endl;  // Should Print 6.8597
    std::cout << spinach[0] << std::endl; // Should Print 7
    return 0;
}
    // implement << operator for piping in kernel output?
    // implement dispatch() and continue() class methods?

    /* Common Pitfalls

        kernels don't do type promotion, so a literal 3.14 is treated as a double by kernels.
        If you're using floats, make sure to pass it in as 3.14f to get the expected result.

        order of arguments matters in chlorine. There's no way for me to warn you ahead of time
        so as with any other program you write, make sure the arguments you pass to execute are
        listed in the same order as you listed in the kernel.
    */
