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

    ch::Worker busybot;
    busybot.set_kernel("default.cl");
    busybot.execute("add", spam, bacon, 12.1f, cheese);
    std::cout << spam[0] << std::endl;
    std::cout << eggs[0] << std::endl;
    std::cout << bacon[0] << std::endl;
    return 0;
}


    // http://stackoverflow.com/questions/21512678/check-at-compile-time-is-a-template-type-a-vector
    // http://stackoverflow.com/questions/12042824/how-to-write-a-type-trait-is-container-or-is-vector
    // if array.size() < mGlobal[0]
    // if array.front().size() < mGlobal[1], etc.
    // store a reference to the original container?


    // should do ifdefs for std::valarray, std::vector, etc.
    //http://stackoverflow.com/questions/1745942/c-template-parameter-in-array-dimension
    //^ for C arrays, and how to handle std::array?
    // void Worker::create_buffer()
        // size_t array_size = V.size() * sizeof(T);
    // void dispatch(); // call?
    // void continue(); // re-use existing buffers/primitives in same order
