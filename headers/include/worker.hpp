// Chlorine Main Header
#ifndef CHLORINE_WORKER
#define CHLORINE_WORKER

namespace ch
{
    class Worker
    {
    public:

        // Constructors
        Worker(); // Default Constructor

        // Proposed Class Methods
        void set_platform(unsigned int platform);
        void set_device(unsigned int device);
        void set_kernel(std::string kernel_source);

       // Handle the Base Case
        void execute(std::string kernel_function) {};

        template<typename T, typename ... Params>
        void execute(std::string kernel_function,
                     std::vector<T> & vector,
                     Params && ... parameters)
        {
            std::cout << "I am a Vector!\n";
            std::cout << "Setting Vector Element Zero to 0!\n";
            vector[0] = 0;
            execute(kernel_function, parameters...);
        }

        template<typename T, typename ... Params>
        void execute(std::string kernel_function,
                     std::valarray<T> & valarray,
                     Params && ... parameters)
        {
            std::cout << "I am a Valarray!\n";
            std::cout << "Setting Valarray Element Zero to 0!\n";
            valarray[0] = 0;
            execute(kernel_function, parameters...);
        }

        // Primitive Types
        template<typename T, typename ... Params>
        void execute(std::string kernel_function,
                     T argument,
                     Params && ... parameters)
        {
            std::cout << "I am a Type! " << argument << "\n";
            execute(kernel_function, parameters...);
        }

    private:

        // Containers
        std::map<std::string, cl::Kernel> mKernels;
        std::map<std::string, cl::Buffer> mBuffers;

        cl::CommandQueue mQueue;
        cl::Context      mContext;
        cl::Device       mDevice;
        cl::Platform     mPlatform;
        cl::Program      mProgram;

    };

    // Default Constructor
    Worker::Worker()
    {
        set_platform(0);
        set_device(0);
        set_kernel("default.cl");

    }

    void Worker::set_platform(unsigned int platform)
    {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(& platforms);
        mPlatform = platforms[platform];
    }

    void Worker::set_device(unsigned int device)
    {
        std::vector<cl::Device> devices;
        mPlatform.getDevices(CL_DEVICE_TYPE_DEFAULT, & devices);
        mContext = cl::Context(devices);
        mDevice = devices[device];
        mQueue = cl::CommandQueue(mContext, mDevice, CL_QUEUE_PROFILING_ENABLE);
    }

    void Worker::set_kernel(std::string kernel_source)
    {
        // Read Contents of Kernel
        std::ifstream fd(kernel_source);
        std::string kernel(std::istreambuf_iterator<char>(fd),
                          (std::istreambuf_iterator<char>()));

        // Build Kernel Using the Current Context
        cl::Program::Sources source(1, std::make_pair(
            kernel.c_str(), kernel.length()+1));
        mProgram = cl::Program(mContext, source);
        mProgram.build(mContext.getInfo<CL_CONTEXT_DEVICES>());

        // Associate Kernel Objects to String Keys
        std::vector<cl::Kernel> kernels;
        mProgram.createKernels(& kernels);
        mKernels.clear();
        for (auto &i : kernels)
           mKernels[i.getInfo<CL_KERNEL_FUNCTION_NAME>()] = i;
    }
}

#endif
