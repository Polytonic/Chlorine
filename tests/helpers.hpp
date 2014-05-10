// Create a Headless Chlorine Worker
ch::Worker worker;

SECTION("Read Helper Returns File Contents")
{
    // Read Kernel Source
    std::string kernel = ch::read("tests/kernels/helpers.cl");

    // Define String Literal to Match
    std::string match =
        "// Test the Kernel Read Function\n"
        "__kernel void read(__global int * a)\n"
        "{\n"
        "    unsigned int i = get_global_id(0);\n"
        "    a[i] = 0;\n"
        "}\n";

    // Assert Kernel Source is Equivalent
    CHECK(kernel == match);
}
