#ifndef CHLORINE_UTILITIES
#define CHLORINE_UTILITIES

namespace ch
{
    // Tokenize an Input String Using a Specified Delimiter
    static std::vector<std::string> split(const std::string & s, char delim = ' ')
    {
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim))
            elems.push_back(item);
        return elems;
    }
}

#endif
