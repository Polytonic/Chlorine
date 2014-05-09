// Chlorine Header
#ifndef CHLORINE
#define CHLORINE

// Include OpenCL C++ Bindings
#pragma GCC diagnostic push
#pragma GCC system_header
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

        // Worker Constructors
        Worker(std::string const & filename, unsigned int const platform = 0, unsigned int const device = 0);
        Worker(      /* No Filename */       unsigned int const platform = 0, unsigned int const device = 0);

        // Disable Copy and Assignment Constructors
        Worker(Worker const &) = delete;
        Worker & operator=(Worker const &) = delete;

        // Overloaded Stream Operators
        friend std::ostream & operator<<(std::ostream& os, const Worker & w);
        friend Worker       & operator>>(Worker & worker, std::string const & kernel_source);

        // Class Methods
        void set_platform(unsigned int const platform);
        void set_device(unsigned int const device);
        std::string build_kernel(std::string const & kernel_source);

        // Handle the Base Case
        template<unsigned int const argn = 0>
        void execute(std::string const & kernel_function);

        // Handle Primitive Types
        template<unsigned int const argn = 0, typename T, typename ... Params>
        typename std::enable_if<std::is_arithmetic<T>::value>::type
        execute(std::string const & kernel_function, T primitive, Params && ... parameters);

        // Handle C-Style Arrays
        template<unsigned int const argn = 0, class T, size_t const N, typename ... Params>
        void execute(std::string const & kernel_function, T (&array) [N], Params && ... parameters);

        // Handle STL Arrays
        template<unsigned int const argn = 0, class T, size_t const N, typename ... Params>
        void execute(std::string const & kernel_function, std::array<T, N> & array, Params && ... parameters);

        // Handle Other STL Containers
        template<unsigned int const argn = 0, template<typename ...> class V, typename T, typename ... Params>
        void execute(std::string const & kernel_function, V<T> & array, Params && ... parameters);

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
    std::ostream & operator<<(std::ostream& os, const Worker & w)
    {
        return os << w.mProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(w.mDevice) << std::endl;
    }

    // Overload Stream Operator >> to Accept Kernel Strings
    Worker & operator>>(Worker & worker, std::string const & kernel_source)
    {
        std::cout << worker.build_kernel(kernel_source);
        return worker;
    }

    // Read the Contents of the Given Filename
    std::string read(std::string const & filename)
    {
        // Read Contents of Kernel
        std::ifstream fd(filename);
        return std::string(std::istreambuf_iterator<char>(fd),
                          (std::istreambuf_iterator<char>()));
    }

    // Filename Constructor
    Worker::Worker(std::string const & filename, unsigned int const platform, unsigned int const device)
    {
        set_platform(platform);
        set_device(device);
        std::cout << build_kernel(read(filename));
    }

    // Default Constructor
    Worker::Worker(unsigned int const platform, unsigned int const device)
    {
        set_platform(platform);
        set_device(device);
    }

    // Selects the Specified OpenCL Platform
    void Worker::set_platform(unsigned int const platform)
    {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(& platforms);
        mPlatform = platforms[platform];
    }

    // Selects the Specified OpenCL Device
    void Worker::set_device(unsigned int const device)
    {
        std::vector<cl::Device> devices;
        mPlatform.getDevices(CL_DEVICE_TYPE_DEFAULT, & devices);
        mContext = cl::Context(devices);
        mDevice = devices[device];
        mQueue = cl::CommandQueue(mContext, mDevice, CL_QUEUE_PROFILING_ENABLE);
    }

    // Builds an OpenCL Kernel from a Program String
    std::string Worker::build_kernel(std::string const & kernel_source)
    {
        // Build Kernel Using the Current Context
        cl::Program::Sources source(1, std::make_pair(kernel_source.c_str(), kernel_source.length()));
        mProgram = cl::Program(mContext, source);
        mProgram.build(mContext.getInfo<CL_CONTEXT_DEVICES>());

        // Associate Kernel Objects to String Keys
        std::vector<cl::Kernel> kernels;
        mProgram.createKernels(& kernels);
        mKernels.clear();
        for (auto &i : kernels)
            mKernels[i.getInfo<CL_KERNEL_FUNCTION_NAME>()] = i;

        // Return the Kernel Build Log
        return mProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(mDevice);
    }

    // Handle the Base Case
    template<unsigned int const argn>
    void Worker::execute(std::string const & kernel_function)
    {
        // Perform the Calculation and Read Data from Memory Buffers
        mQueue.enqueueNDRangeKernel(mKernels[kernel_function], mOffset, mGlobal, mLocal);
        for (auto &i : mBuffers)
            mQueue.enqueueUnmapMemObject(i.first,
            mQueue.enqueueMapBuffer(i.first, CL_TRUE, CL_MAP_READ, 0, i.second));
            mBuffers.clear();
    }

    // Handle Primitive Types
    template<unsigned int const argn, typename T, typename ... Params>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    Worker::execute(std::string const & kernel_function, T primitive, Params && ... parameters)
    {
        mKernels[kernel_function].setArg(argn, primitive);
        execute<argn+1>(kernel_function, parameters...);
    }

    // Handle C-Style Arrays
    template<unsigned int const argn, class T, size_t const N, typename ... Params>
    void Worker::execute(std::string const & kernel_function, T (&array) [N], Params && ... parameters)
    {
        size_t array_size = N * sizeof(array[0]);
        if (N > mGlobal[0]) { mGlobal = cl::NDRange(N); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        execute<argn+1>(kernel_function, parameters...);
    }

    // Handle STL Arrays
    template<unsigned int const argn, class T, size_t const N, typename ... Params>
    void Worker::execute(std::string const & kernel_function, std::array<T, N> & array, Params && ... parameters)
    {
        size_t array_size = array.size() * sizeof(T);
        if (array.size() > mGlobal[0]) { mGlobal = cl::NDRange(array.size()); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        execute<argn+1>(kernel_function, parameters...);
    }

    // Handle Other STL Containers
    template<unsigned int const argn, template<typename ...> class V, typename T, typename ... Params>
    void Worker::execute(std::string const & kernel_function, V<T> & array, Params && ... parameters)
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
