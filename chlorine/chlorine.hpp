// Chlorine Header
#ifndef CHLORINE
#define CHLORINE

// Include OpenCL C++ Bindings
#pragma GCC diagnostic push
#pragma GCC system_header
#define __CL_ENABLE_EXCEPTIONS
#include "cl.hpp"
#pragma GCC diagnostic pop

// Standard Library Headers
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace ch
{
    class Worker
    {
    public:

        // Available Worker Constructors
        Worker(std::string filename, unsigned int platform = 0, unsigned int device = 0);
        Worker(  /* No Filename */   unsigned int platform = 0, unsigned int device = 0);

        // Disable Copy and Assignment Constructors
        Worker(const Worker &) = delete;
        Worker & operator=(const Worker &) = delete;

        // Proposed Class Methods
        void set_platform(unsigned int platform);
        void set_device(unsigned int device);
        void set_kernel(std::string kernel_source);

        // Handle the Base Case
        template<unsigned int argn = 0>
        void execute(std::string kernel_function);

        // Handle Primitive Types
        template<unsigned int argn = 0, typename T, typename ... Params>
        typename std::enable_if<std::is_arithmetic<T>::value>::type
        execute(std::string kernel_function, T primitive, Params && ... parameters);

        // Handle C-Style Arrays
        template<unsigned int argn = 0, class T, size_t N, typename ... Params>
        void execute(std::string kernel_function, T (&array) [N], Params && ... parameters);

        // Handle STL Arrays
        template<unsigned int argn = 0, class T, size_t N, typename ... Params>
        void execute(std::string kernel_function, std::array<T, N> & array, Params && ... parameters);

        // Handle Other STL Containers
        template<unsigned int argn = 0, template<typename ...> class V, typename T, typename ... Params>
        void execute(std::string kernel_function, V<T> & array, Params && ... parameters);

    private:

        // Components
        cl::CommandQueue mQueue;
        cl::Context      mContext;
        cl::Device       mDevice;
        cl::Platform     mPlatform;
        cl::Program      mProgram;

        // Containers
        std::vector<std::pair<cl::Buffer, size_t>> mBuffers;
        std::map<std::string, cl::Kernel> mKernels;

        // Data Ranges
        cl::NDRange mGlobal = cl::NDRange(0, 0, 0);
        cl::NDRange mLocal  = cl::NullRange;
        cl::NDRange mOffset = cl::NullRange;

    };

    // Overload Stream Operator << to Print Build Information
    std::ostream& operator<<(std::ostream& os, const Worker & w)
    {
        os << "Hello World" << std::endl;
        return os;
    }

    // Overload Stream Operator >> to Accept Kernel Strings
    Worker & operator>>(Worker & worker, const std::string kernel_source)
    {
        worker.set_kernel(kernel_source);
        return worker;
    }

    // Read the Contents of the Given Filename
    std::string read(std::string filename)
    {
        // Read Contents of Kernel
        std::ifstream fd(filename);
        std::string contents(std::istreambuf_iterator<char>(fd),
                            (std::istreambuf_iterator<char>()));
        return contents;
    }

    // Filename Constructor
    Worker::Worker(std::string filename, unsigned int platform, unsigned int device)
    {
        set_platform(platform);
        set_device(device);
        set_kernel(read(filename));
    }

    // Default Constructor
    Worker::Worker(unsigned int platform, unsigned int device)
    {
        set_platform(platform);
        set_device(device);
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
        // Build Kernel Using the Current Context
        cl::Program::Sources source(1, std::make_pair(kernel_source.c_str(), kernel_source.length()));
        mProgram = cl::Program(mContext, source);
        try { mProgram.build(mContext.getInfo<CL_CONTEXT_DEVICES>()); }
        catch (cl::Error err) { std::cerr << mProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(mDevice); }

        // Associate Kernel Objects to String Keys
        std::vector<cl::Kernel> kernels;
        mProgram.createKernels(& kernels);
        mKernels.clear();
        for (auto &i : kernels)
            mKernels[i.getInfo<CL_KERNEL_FUNCTION_NAME>()] = i;
    }

    // Handle the Base Case
    template<unsigned int argn>
    void Worker::execute(std::string kernel_function)
    {
        // Perform the Calculation and Read Data from Memory Buffers
        mQueue.enqueueNDRangeKernel(mKernels[kernel_function], mOffset, mGlobal, mLocal);
        for (auto &i : mBuffers)
            mQueue.enqueueUnmapMemObject(i.first,
            mQueue.enqueueMapBuffer(i.first, CL_TRUE, CL_MAP_READ, 0, i.second));
            mBuffers.clear();
    }

    // Handle Primitive Types
    template<unsigned int argn, typename T, typename ... Params>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    Worker::execute(std::string kernel_function, T primitive, Params && ... parameters)
    {
        mKernels[kernel_function].setArg(argn, primitive);
        execute<argn+1>(kernel_function, parameters...);
    }

    // Handle C-Style Arrays
    template<unsigned int argn, class T, size_t N, typename ... Params>
    void Worker::execute(std::string kernel_function, T (&array) [N], Params && ... parameters)
    {
        size_t array_size = N * sizeof(array[0]);
        if (N > mGlobal[0]) { mGlobal = cl::NDRange(N); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        execute<argn+1>(kernel_function, parameters...);
    }

    // Handle STL Arrays
    template<unsigned int argn, class T, size_t N, typename ... Params>
    void Worker::execute(std::string kernel_function, std::array<T, N> & array, Params && ... parameters)
    {
        size_t array_size = array.size() * sizeof(T);
        if (array.size() > mGlobal[0]) { mGlobal = cl::NDRange(array.size()); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        execute<argn+1>(kernel_function, parameters...);
    }

    // Handle Other STL Containers
    template<unsigned int argn, template<typename ...> class V, typename T, typename ... Params>
    void Worker::execute(std::string kernel_function, V<T> & array, Params && ... parameters)
    {
        size_t array_size = array.size() * sizeof(T);
        if (array.size() > mGlobal[0]) { mGlobal = cl::NDRange(array.size()); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        execute<argn+1>(kernel_function, parameters...);
    }
};

#endif
