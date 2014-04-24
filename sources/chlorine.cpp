#include "chlorine.hpp"

int main()
{
    std::vector<int>    spam (10, 3);
    std::vector<double> eggs (10, 2.7182);

    ch::Worker busybot;
    long double n = 6.5;

    std::cout << "Spam of Zero: " << spam[0] << std::endl;
    busybot.execute("add");
    busybot.execute("add", spam, 5, eggs, 4.4, n);
    std::cout << "Spam of Zero: " << spam[0] << std::endl;
    return 0;
}
