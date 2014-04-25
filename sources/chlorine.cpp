#include "chlorine.hpp"

int main()
{
    std::vector<int>    spam  (10, 3);
    std::vector<float>  eggs  (10, 2.7182f);
    std::valarray<int>  bacon (99, 10); // valarray constructor is backwards

    ch::Worker busybot;
    busybot.set_kernel("default.cl");
    busybot.execute("add", spam, eggs, 100);
    std::cout << spam[1] << std::endl;
    std::cout << eggs[1] << std::endl;
    return 0;
}
