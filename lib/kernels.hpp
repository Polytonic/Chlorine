#ifndef CHLORINE_KERNELS
#define CHLORINE_KERNELS

void load_kernels(std::string kernel_source)
{
    // Load Kernel from Kernel Source
    std::ifstream fn (kernel_source.c_str());
    std::string prgm_str (std::istreambuf_iterator<char>(fn),
                         (std::istreambuf_iterator<char>()));

    // Check File Open Status
    if (fn.is_open() == false || prgm_str.length() <= 0)
    {
        std::cerr << "std::ifstream: ";
        perror(kernel_source.c_str());
        return exit(EXIT_FAILURE);
    }   fn.close(); // Close the File

    // Generate Kernel From Kernel Source
    cl::Program::Sources source (1,
        std::make_pair(prgm_str.c_str(),
                       prgm_str.length()+1));

    ch::Context = cl::Context(ch::devices);
    ch::Program = cl::Program(ch::Context, source);

    // Print Build Log on Compilation Failure
    try { ch::Program.build(ch::devices);
    } catch (cl::Error exception) {
        std::cerr << "Printing Build Log\n\n"
                  << ch::Program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(ch::Device)
                  << "Please Resolve Errors" << std::endl;
    } ch::Program.createKernels(& ch::kernels);
}

/*
    // Print Available Kernel Functions
    for (unsigned int i = 0; i < ch::kernels.size(); i++)
        std::cerr << ch::kernels[i].getInfo<CL_KERNEL_FUNCTION_NAME>();
        std::cerr << std::endl;
*/

#endif