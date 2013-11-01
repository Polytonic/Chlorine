#ifndef CHLORINE_UTILITIES
#define CHLORINE_UTILITIES

namespace ch
{
    // Tokenize an Input String Using a Specified Delimiter
    std::vector<std::string> split(const std::string & s, char delim = ' ')
    {
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim))
            elems.push_back(item);
        return elems;
    }

    // Parse Arguments Passed on the Command Line
    void parse_arguments(int argc, char * argv[])
    {
        // Local Variables
        unsigned int flag;
        std::string args;

        // Dynamically Determine the Option Flag Separators
        for (flag = 0; flag < sizeof(opts) / sizeof(option); flag++)
        {
            args += opts[flag].val; // Append Option Letter
                 if (opts[flag].has_arg == 1) { args += ":";  }
            else if (opts[flag].has_arg == 2) { args += "::"; }
        }

        // Iterate Through Available Options
        while ((flag = getopt_long(argc, argv, args.c_str(), opts, NULL)) != -1)
            switch (flag)
            {
                case 'h': std::cout << "Help Requested"; break;
                case '?': default: return exit(EXIT_FAILURE);
            }
    }
}

#endif
