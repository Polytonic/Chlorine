#include "chlorine.hpp"
#include <vector>
int main()
{
    ch::Worker busybot;
    //fill vectors
    std::vector<float> f1(1.0,30);
    std::vector<int> i1(3,10); 
    std::vector<double> d1(1.7,36);
    busybot.push(f1,i1,d1);    
    return 0;
}
