#include "chlorine.hpp"

int main()
{
    std::vector<int>    spam  (10, 3);
    std::vector<double> eggs  (10, 2.7182);
    std::valarray<int>  bacon (99, 10); // valarray constructor is backwards

    ch::Worker busybot;
    long double n = 6.5;

    std::cout << "Spam of Zero: " << spam[0] << std::endl;
    busybot.execute("add");
    std::cout << "Bacon of Zero: " << bacon[0] << std::endl;
    busybot.execute("add", bacon);
    busybot.execute("add", bacon, 10, 15, 20.0);
    std::cout << "Bacon of Zero: " << bacon[0] << std::endl;
    busybot.execute("add", spam, 5, eggs, 4.4, n);
    busybot.execute("add", 1);

    std::cout << "Spam of Zero: " << spam[0] << std::endl;
    return 0;
}
