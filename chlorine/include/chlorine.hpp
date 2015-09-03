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
    // Forward Declare Helper Functions for Xcode Tooltips
    unsigned int elapsed(cl::Event const & event);
    std::string read(std::string const & filename);

    /**
        Workers are responsible for abstracting away the OpenCL interface. They
        setup OpenCL, and handle transferring data back and forth between host
        and device memory. Workers expose a clean, concise interface, allowing
        you to transparently work with your data with little to no overhead.

        @note documentation blocks are available above method definitions.
     */
    class Worker
    {
    public:

        // Worker Constructors
        Worker(std::string const & filename = "", unsigned int const platform = 0, unsigned int const device = 0);

        // Disable Copy and Assignment Constructors
        Worker(Worker const &) = delete;
        Worker & operator=(Worker const &) = delete;

        // Overloaded Stream Operators
        friend std::ostream & operator<<(std::ostream & os, Worker const & w);
        friend Worker       & operator>>(Worker & worker, std::string const & kernel_source);

        // Class Methods
        void set_platform(unsigned int const platform);
        void set_device(unsigned int const device);
        std::string build_kernel(std::string const & kernel_source);

        // Handle the Base Case
        template<unsigned int const argn = 0>
        cl::Event call(std::string const & kernel_function);

        // Handle Primitive Types
        template<unsigned int const argn = 0, typename T,
                 typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr, typename ... Params>
        cl::Event call(std::string const & kernel_function, T primitive, Params && ... parameters);

        // Handle C-Style Arrays
        template<unsigned int const argn = 0, class T, size_t const N, typename ... Params>
        cl::Event call(std::string const & kernel_function, T (&array) [N], Params && ... parameters);

        // Handle STL Arrays
        template<unsigned int const argn = 0, class T, size_t const N, typename ... Params>
        cl::Event call(std::string const & kernel_function, std::array<T, N> & array, Params && ... parameters);

        // Handle Other STL Containers
        template<unsigned int const argn = 0, template<typename ...> class V, typename T, typename ... Params>
        cl::Event call(std::string const & kernel_function, V<T> & array, Params && ... parameters);

    private:

        // Components
        cl::CommandQueue mQueue;
        cl::Context      mContext;
        cl::Device       mDevice;
        cl::Event        mEvent;
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

    /**
        Overloads the insertion operator to display build information if a
        kernel failed to compile. If the build was successful, this will produce
        an empty build log.

        @param std::ostream the output stream to write the build log to.
        @param ch::Worker the Chlorine worker to retrieve the build log from.
        @returns an output stream containing build information.
     */
    std::ostream & operator<<(std::ostream & os, Worker const & w)
    {
        return os << w.mProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(w.mDevice) << std::endl;
    }

    /**
        Overloads the extraction operator to accept the source of a kernel
        and attempts to build it on the currently specified platform and device.

        @param ch::Worker the Chlorine worker to build the kernel on.
        @param std::string the source contents of an OpenCL kernel.
        @returns a Chlorine worker instance.
     */
    Worker & operator>>(Worker & worker, std::string const & kernel_source)
    {
        std::cout << worker.build_kernel(kernel_source);
        return worker;
    }

    /**
        Determines the elapsed time of a given event. This is typically used to
        compute the running time of the kernel associated with this event. This
        does not include time spent transferring data between host and device.

        @param cl::Event the OpenCL event to retrieve profiling data from.
        @returns the elapsed execution time of the event, in nanoseconds.
     */
    unsigned int elapsed(cl::Event const & event)
    {
        return event.getProfilingInfo<CL_PROFILING_COMMAND_END>()
             - event.getProfilingInfo<CL_PROFILING_COMMAND_START>();
    }

    /**
        Efficiently loads the contents of a file into a string. This is mainly
        useful for reading OpenCL kernel files, instead of inlining kernels in
        source code using concatenated string literals.

        @param std::string the name of an input file.
        @returns a string containing the contents of the input file.
     */
    std::string read(std::string const & filename)
    {
        // Read Contents of Kernel
        std::ifstream fd(filename);
        return std::string(std::istreambuf_iterator<char>(fd),
                          (std::istreambuf_iterator<char>()));
    }

    /**
        Constructs a Chlorine worker and initializes OpenCL. Typically you will
        call this constructor by only passing the name of a kernel source file.
        If you need to specifically target a different platform or device, use
        the bundled `clinfo` program to display information about the OpenCL
        runtimes available on your system.

        @param std::string (optional) the path to a kernel source file.
        @param unsigned (optional) the integer index of the platform to use.
        @param unsigned (optional) the integer index of the device to use.
     */
    Worker::Worker(std::string const & filename, unsigned int const platform, unsigned int const device)
    {
        set_platform(platform);
        set_device(device);

        if (filename.empty() == false)
            std::cout << build_kernel(read(filename));
    }

    /**
        Specifies the OpenCL platform to use. If you are unsure which platforms
        are available on your system, please use the bundled `clinfo` program to
        display an ordered list of available OpenCL platforms.

        @param unsigned the integer index of the platform to use.
     */
    void Worker::set_platform(unsigned int const platform)
    {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(& platforms);
        mPlatform = platforms[platform];
    }

    /**
        Specifies the OpenCL device to use. If you are unsure which devices are
        available on your system, please use the bundled `clinfo` program to
        display an ordered list of available OpenCL devices.

        @param unsigned the integer index of the device to use.
     */
    void Worker::set_device(unsigned int const device)
    {
        std::vector<cl::Device> devices;
        mPlatform.getDevices(CL_DEVICE_TYPE_DEFAULT, & devices);
        mContext = cl::Context(devices);
        mDevice = devices[device];
        mQueue = cl::CommandQueue(mContext, mDevice, CL_QUEUE_PROFILING_ENABLE);
    }

    /**
        Builds the kernel on the target device and platform. Note that this
        operation is performed at runtime. i.e., kernels are just-in-time
        compiled, for portability. If the build was successful, this will
        produce an empty build log.

        @param std::string the source contents of an OpenCL kernel.
        @returns a string containing the OpenCL build log.
     */
    std::string Worker::build_kernel(std::string const & kernel_source)
    {
        // Build Kernel Using the Current Context
        cl::Program::Sources source(1, std::make_pair(kernel_source.c_str(), kernel_source.length()));
        mProgram = cl::Program(mContext, source);
        mProgram.build(mContext.getInfo<CL_CONTEXT_DEVICES>());

        // Associate Kernel Objects to String Keys
        std::vector<cl::Kernel> kernels;
        mProgram.createKernels(& kernels);
        for (auto &i : kernels)
            mKernels[i.getInfo<CL_KERNEL_FUNCTION_NAME>()] = i;

        // Return the Kernel Build Log
        return mProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(mDevice);
    }

    /**
        Enqueues the kernel for execution on the OpenCL device. Buffer data is
        automatically transferred back into the input data structures on the
        host after the kernel has finished executing on the device.

        @note this is an overloaded, recursive, variadic template method.
        @param std::string the name of a kernel function.
        @returns an OpenCL event object containing profiling data.
     */
    template<unsigned int const argn>
    cl::Event Worker::call(std::string const & kernel_function)
    {
        // Perform the Calculation and Read Data from Memory Buffers
        mQueue.enqueueNDRangeKernel(mKernels[kernel_function], mOffset, mGlobal, mLocal, NULL, & mEvent);
        for (auto &i : mBuffers)
            mQueue.enqueueUnmapMemObject(i.first,
            mQueue.enqueueMapBuffer(i.first, CL_TRUE, CL_MAP_READ, 0, i.second));
            mBuffers.clear();

        // Return OpenCL Event Object Containing Profiling Data
        return mEvent;
    }

    /**
        Sets the kernel argument at the current index to the value of the given
        arithmetic primitive data type. For a specific list of fundamental data
        types, please consult http://en.cppreference.com/w/cpp/language/types

        @note this is an overloaded, recursive, variadic template method.
        @param <T> a fundamental data type.
        @returns an OpenCL event object containing profiling data.
     */
    template<unsigned int const argn, typename T,
             typename std::enable_if<std::is_arithmetic<T>::value>::type*, typename ... Params>
    cl::Event Worker::call(std::string const & kernel_function, T primitive, Params && ... parameters)
    {
        mKernels[kernel_function].setArg(argn, primitive);
        return call<argn+1>(kernel_function, parameters...);
    }

    /**
        Sets the kernel argument at the current index to an OpenCL buffer
        mapped to the contents of a C-style array. The array size is inferred
        through operator decay.

        @note this is an overloaded, recursive, variadic template method.
        @param <T> a C-style array containing your data.
        @returns an OpenCL event object containing profiling data.
     */
    template<unsigned int const argn, class T, size_t const N, typename ... Params>
    cl::Event Worker::call(std::string const & kernel_function, T (&array) [N], Params && ... parameters)
    {
        size_t array_size = N * sizeof(array[0]);
        if (N > mGlobal[0]) { mGlobal = cl::NDRange(N); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        return call<argn+1>(kernel_function, parameters...);
    }

    /**
        Sets the kernel argument at the current index to an OpenCL buffer
        mapped to the contents of a std::array.

        @note this is an overloaded, recursive, variadic template method.
        @param <T> a std::array containing your data.
        @returns an OpenCL event object containing profiling data.
     */
    template<unsigned int const argn, class T, size_t const N, typename ... Params>
    cl::Event Worker::call(std::string const & kernel_function, std::array<T, N> & array, Params && ... parameters)
    {
        size_t array_size = array.size() * sizeof(T);
        if (array.size() > mGlobal[0]) { mGlobal = cl::NDRange(array.size()); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        return call<argn+1>(kernel_function, parameters...);
    }

    /**
        Sets the kernel argument at the current index to an OpenCL buffer
        mapped to the contents of a data structure `V` with constructor matching
        the form V<T>, typically std::vector or std::valarray. Other containers
        may also be supported. Your mileage may vary.

        @note this is an overloaded, recursive, variadic template method.
        @param V<T> a std::vector<T> or std::valarray<T> containing your data.
        @returns an OpenCL event object containing profiling data.
     */
    template<unsigned int const argn, template<typename ...> class V, typename T, typename ... Params>
    cl::Event Worker::call(std::string const & kernel_function, V<T> & array, Params && ... parameters)
    {
        size_t array_size = array.size() * sizeof(T);
        if (array.size() > mGlobal[0]) { mGlobal = cl::NDRange(array.size()); }
        cl::Buffer buffer = cl::Buffer(mContext, CL_MEM_USE_HOST_PTR, array_size, & array[0]);
        mBuffers.push_back(std::make_pair(buffer, array_size));
        mKernels[kernel_function].setArg(argn, buffer);
        return call<argn+1>(kernel_function, parameters...);
    }
};

#endif
