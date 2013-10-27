#ifndef CHLORINE_CLINFO
#define CHLORINE_CLINFO

#include "chlorine.hpp"

namespace ch
{
    void get_platform_info(cl::Platform platform)
    {
        // Print Platform Information
        std::cout << std::setw(ch::width) << std::left       << "Platform Name:"
                  << platform.getInfo<CL_PLATFORM_NAME>()    << std::endl
                  << std::setw(ch::width) << std::left       << "Platform Profile:"
                  << platform.getInfo<CL_PLATFORM_PROFILE>() << std::endl
                  << std::setw(ch::width) << std::left       << "Platform Vendor:"
                  << platform.getInfo<CL_PLATFORM_VENDOR>()  << std::endl
                  << std::setw(ch::width) << std::left       << "Platform Version:"
                  << platform.getInfo<CL_PLATFORM_VERSION>() << std::endl;

        // Print Supported Platform Extensions
        std::cout << "Platform Extensions:\n" << std::endl;
        ch::extensions = ch::split(platform.getInfo<CL_PLATFORM_EXTENSIONS>());
        for (unsigned int i = 0; i < ch::extensions.size(); i++)
            std::cout << "\t" << ch::extensions[i] << std::endl;
    }

    void get_device_info(cl::Device device)
    {
        // Print Device Information
        std::cout << std::setw(ch::width) << std::left   << "Device Name:"
                  << device.getInfo<CL_DEVICE_NAME>()    << std::endl
                  << std::setw(ch::width) << std::left   << "Device Profile:"
                  << device.getInfo<CL_DEVICE_PROFILE>() << std::endl
                  << std::setw(ch::width) << std::left   << "Device Vendor:"
                  << device.getInfo<CL_DEVICE_VENDOR>()  << std::endl
                  << std::setw(ch::width) << std::left   << "Device Version:"
                  << device.getInfo<CL_DEVICE_VERSION>() << std::endl;

        // Print Supported Device Extensions
        std::cout << "Device Extensions:\n" << std::endl;
        ch::extensions = ch::split(device.getInfo<CL_DEVICE_EXTENSIONS>());
        for (unsigned int i = 0; i < ch::extensions.size(); i++)
            std::cout << "\t" << ch::extensions[i] << std::endl;

        // Print Supported Device Features
        std::cout << std::endl << "Device Features:\n" << std::endl;
        std::cout << std::setw(ch::width) << std::left                         << "\tAddress Bits:"
                  << device.getInfo<CL_DEVICE_ADDRESS_BITS>()                  << std::endl
                  << std::setw(ch::width) << std::left                         << "\tDevice Available:"
                  << device.getInfo<CL_DEVICE_AVAILABLE>()                     << std::endl
                  << std::setw(ch::width) << std::left                         << "\tCompiler Available:"
                  << device.getInfo<CL_DEVICE_COMPILER_AVAILABLE>()            << std::endl
                  << std::setw(ch::width) << std::left                         << "\tLittle Endian:"
                  << device.getInfo<CL_DEVICE_ENDIAN_LITTLE>()                 << std::endl
                  << std::setw(ch::width) << std::left                         << "\tError Correction Support:"
                  << device.getInfo<CL_DEVICE_ERROR_CORRECTION_SUPPORT>()      << std::endl
                  << std::setw(ch::width) << std::left                         << "\tGlobal Memory Cache Size:"
                  << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE>()         << std::endl
                  << std::setw(ch::width) << std::left                         << "\tGlobal Memory Cache Type:"
                  << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_TYPE>()         << std::endl
                  << std::setw(ch::width) << std::left                         << "\tGlobal Memory Cache Line Size:"
                  << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE>()     << std::endl
                  << std::setw(ch::width) << std::left                         << "\tGlobal Memory Size:"
                  << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>()               << std::endl
                  << std::setw(ch::width) << std::left                         << "\tUnified Memory Subsystem:"
                  << device.getInfo<CL_DEVICE_HOST_UNIFIED_MEMORY>()           << std::endl
                  << std::setw(ch::width) << std::left                         << "\tImage Support:"
                  << device.getInfo<CL_DEVICE_IMAGE_SUPPORT>()                 << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax 2D Image Height:"
                  << device.getInfo<CL_DEVICE_IMAGE2D_MAX_HEIGHT>()            << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax 2D Image Width:"
                  << device.getInfo<CL_DEVICE_IMAGE2D_MAX_WIDTH>()             << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax 3D Image Depth:"
                  << device.getInfo<CL_DEVICE_IMAGE3D_MAX_DEPTH>()             << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax 3D Image Height:"
                  << device.getInfo<CL_DEVICE_IMAGE3D_MAX_HEIGHT>()            << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax 3D Image Width:"
                  << device.getInfo<CL_DEVICE_IMAGE3D_MAX_WIDTH>()             << std::endl
                  << std::setw(ch::width) << std::left                         << "\tLocal Memory Size:"
                  << device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>()                << std::endl
                  << std::setw(ch::width) << std::left                         << "\tLocal Memory Type:"
                  << device.getInfo<CL_DEVICE_LOCAL_MEM_TYPE>()                << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Clock Frequency:"
                  << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>()           << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Compute Units:"
                  << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()             << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Constant Arguments:"
                  << device.getInfo<CL_DEVICE_MAX_CONSTANT_ARGS>()             << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Constant Buffer Size:"
                  << device.getInfo<CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE>()      << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Memory Allocation Size:"
                  << device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>()            << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Kernel Parameter Size:"
                  << device.getInfo<CL_DEVICE_MAX_PARAMETER_SIZE>()            << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Simultaneous Image Objects:"
                  << device.getInfo<CL_DEVICE_MAX_READ_IMAGE_ARGS>()           << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Samplers:"
                  << device.getInfo<CL_DEVICE_MAX_SAMPLERS>()                  << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Work Group Size:"
                  << device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>()           << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Work Item Dimensions:"
                  << device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>()      << std::endl
                  << std::setw(ch::width) << std::left                         << "\tMax Write Image Arguments:"
                  << device.getInfo<CL_DEVICE_MAX_WRITE_IMAGE_ARGS>()          << std::endl
                  << std::setw(ch::width) << std::left                         << "\tBase Memory Address Alignment:"
                  << device.getInfo<CL_DEVICE_MEM_BASE_ADDR_ALIGN>()           << std::endl
                  << std::setw(ch::width) << std::left                         << "\tNative Vector Width (CHAR):"
                  << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR>()      << std::endl
                  << std::setw(ch::width) << std::left                         << "\tNative Vector Width (SHORT):"
                  << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT>()     << std::endl
                  << std::setw(ch::width) << std::left                         << "\tNative Vector Width (INT):"
                  << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_INT>()       << std::endl
                  << std::setw(ch::width) << std::left                         << "\tNative Vector Width (LONG):"
                  << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG>()      << std::endl
                  << std::setw(ch::width) << std::left                         << "\tNative Vector Width (FLOAT):"
                  << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT>()     << std::endl
                  << std::setw(ch::width) << std::left                         << "\tNative Vector Width (DOUBLE):"
                  << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE>()    << std::endl
                  << std::setw(ch::width) << std::left                         << "\tNative Vector Width (HALF):"
                  << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF>()      << std::endl
                  << std::setw(ch::width) << std::left                         << "\tOpenCL C Version:"
                  << device.getInfo<CL_DEVICE_OPENCL_C_VERSION>()              << std::endl
                  << std::setw(ch::width) << std::left                         << "\tParent Device:"
                  << device.getInfo<CL_DEVICE_PARENT_DEVICE>()                 << std::endl
                  << std::setw(ch::width) << std::left                         << "\tCurrent Platform:"
                  << device.getInfo<CL_DEVICE_PLATFORM>()                      << std::endl
                  << std::setw(ch::width) << std::left                         << "\tPreferred Vector Width (CHAR):"
                  << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR>()   << std::endl
                  << std::setw(ch::width) << std::left                         << "\tPreferred Vector Width (SHORT):"
                  << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT>()  << std::endl
                  << std::setw(ch::width) << std::left                         << "\tPreferred Vector Width (INT):"
                  << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT>()    << std::endl
                  << std::setw(ch::width) << std::left                         << "\tPreferred Vector Width (LONG):"
                  << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG>()   << std::endl
                  << std::setw(ch::width) << std::left                         << "\tPreferred Vector Width (FLOAT):"
                  << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT>()  << std::endl
                  << std::setw(ch::width) << std::left                         << "\tPreferred Vector Width (DOUBLE):"
                  << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE>() << std::endl
                  << std::setw(ch::width) << std::left                         << "\tPreferred Vector Width (HALF):"
                  << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF>()   << std::endl
                  << std::setw(ch::width) << std::left                         << "\tUser Handles Interop Memory Sync:"
                  << device.getInfo<CL_DEVICE_PREFERRED_INTEROP_USER_SYNC>()   << std::endl
                  << std::setw(ch::width) << std::left                         << "\tProfiling Timer Resolution (ns):"
                  << device.getInfo<CL_DEVICE_PROFILING_TIMER_RESOLUTION>()    << std::endl
                  << std::setw(ch::width) << std::left                         << "\tReference Count:"
                  << device.getInfo<CL_DEVICE_REFERENCE_COUNT>()               << std::endl
                  << std::setw(ch::width) << std::left                         << "\tUnique Vendor Identifier:"
                  << device.getInfo<CL_DEVICE_VENDOR_ID>()                     << std::endl
                  << std::setw(ch::width) << std::left                         << "\tDriver Version:"
                  << device.getInfo<CL_DRIVER_VERSION>()                       << std::endl;

        /*
            CL_DEVICE_BUILT_IN_KERNELS
            CL_DEVICE_DOUBLE_FP_CONFIG
            CL_DEVICE_HALF_FP_CONFIG
            CL_DEVICE_SINGLE_FP_CONFIG
            CL_DEVICE_EXECUTION_CAPABILITIES
            CL_DEVICE_PARTITION_AFFINITY_DOMAIN
            CL_DEVICE_QUEUE_PROPERTIES ( == CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE)


            ### MISSING TEMPLATES OR DON'T WORK WITH DEVICE GET INFO ###
            CL_DEVICE_IMAGE_MAX_BUFFER_SIZE
            CL_DEVICE_IMAGE_MAX_ARRAY_SIZE
            CL_DEVICE_LINKER_AVAILABLE
            CL_DEVICE_MAX_WORK_ITEM_SIZES
            CL_DEVICE_PARTITION_MAX_SUB_DEVICES
            CL_DEVICE_PARTITION_PROPERTIES
            CL_DEVICE_PARTITION_TYPE
            CL_DEVICE_PRINTF_BUFFER_SIZE

            CL_DEVICE_NATIVE_VECTOR_WIDTH returns strange (incorrect?) sizes...
         */

    }
}

#endif
