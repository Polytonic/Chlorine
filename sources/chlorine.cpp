#include "chlorine.hpp"

int main()
{
    std::vector<int>    spam  (10, 3);
    std::vector<int>    ham   (10, 5);
    std::vector<float>  eggs  (10, 2.7182f);
    std::valarray<float>  bacon (99, 10); // valarray constructor is backwards
    std::array<int, 10> spinach = { 9, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    int cheese[10] = { 1, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    std::cout << bacon[0] << std::endl;
    ch::Worker busybot;
    busybot.set_kernel("default.cl");
    busybot.execute("add", spam, bacon, 12.1f, cheese);
    std::cout << spam[0] << std::endl;
    std::cout << eggs[0] << std::endl;
    std::cout << bacon[0] << std::endl;
    return 0;
}
