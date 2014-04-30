#include "chlorine.hpp"
#include <valarray>

int main()
{
    std::vector<int>    spam  (10, 3);
    std::vector<int>    ham   (10, 5);
    std::vector<float>  eggs  (10, 2.7182f);
    std::valarray<float>  bacon (99, 10); // valarray constructor is backwards
    std::array<int, 10> spinach = { 9, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    int cheese[10] = { 1, 5, 5, 5, 5, 5, 5, 5, 5, 5 };


    try{
        ch::Worker busybot(0,0);
        busybot.set_kernel("tests/default.cl");
        busybot.execute("add", spam, bacon, 12.1f, cheese);
    } catch (cl::Error err) { std::cout << err.err() << ":" << err.what() << std::endl; }

    std::cout << spam[0] << std::endl;
    std::cout << eggs[0] << std::endl;
    std::cout << bacon[0] << std::endl;
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
