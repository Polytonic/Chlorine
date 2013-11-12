#ifndef CHLORINE_ERROR
#define CHLORINE_ERROR

namespace ch
{
    // Display Additional Information About the Exception
    int print_exception_string(cl::Error exception)
    {
        fprintf(stderr, "%s (%d) :", exception.what(), exception.err());
        switch(exception.err()) // Lookup the Appropriate Response
        {
            case CL_SUCCESS                                     : std::cerr << "Success";                                           break;
            case CL_DEVICE_NOT_FOUND                            : std::cerr << "Device Not Found";                                  break;
            case CL_DEVICE_NOT_AVAILABLE                        : std::cerr << "Device Not Available";                              break;
            case CL_COMPILER_NOT_AVAILABLE                      : std::cerr << "Compiler Not Available";                            break;
            case CL_MEM_OBJECT_ALLOCATION_FAILURE               : std::cerr << "Memory Object Allocation Failure";                  break;
            case CL_OUT_OF_RESOURCES                            : std::cerr << "Out of Resources";                                  break;
            case CL_OUT_OF_HOST_MEMORY                          : std::cerr << "Out of Host Memory";                                break;
            case CL_PROFILING_INFO_NOT_AVAILABLE                : std::cerr << "Profiling Information Not Available";               break;
            case CL_MEM_COPY_OVERLAP                            : std::cerr << "Memory Copy Overlap";                               break;
            case CL_IMAGE_FORMAT_MISMATCH                       : std::cerr << "Image Format Mismatch";                             break;
            case CL_IMAGE_FORMAT_NOT_SUPPORTED                  : std::cerr << "Image Format Not Supported";                        break;
            case CL_BUILD_PROGRAM_FAILURE                       : std::cerr << "Build Program Failure";                             break;
            case CL_MAP_FAILURE                                 : std::cerr << "Map Failure";                                       break;
            case CL_MISALIGNED_SUB_BUFFER_OFFSET                : std::cerr << "Misaligned Sub-Buffer Offset";                      break;
            case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST   : std::cerr << "Execution Status Error for Events in Wait List";    break;

                // Requires OpenCL 1.1 (Rev33)
                //case CL_COMPILE_PROGRAM_FAILURE                     : std::cerr << "Compile Program Failure";                           break;
                //case CL_LINKER_NOT_AVAILABLE                        : std::cerr << "Linker Not Available";                              break;
                //case CL_LINK_PROGRAM_FAILURE                        : std::cerr << "Link Program Failure";                              break;
                //case CL_DEVICE_PARTITION_FAILED                     : std::cerr << "Device Partition Failed";                           break;
                //case CL_KERNEL_ARG_INFO_NOT_AVAILABLE               : std::cerr << "Kernel Argument Information Not Available";         break;

            case CL_INVALID_VALUE                               : std::cerr << "Invalid Value";                                     break;
            case CL_INVALID_DEVICE_TYPE                         : std::cerr << "Invalid Device Type";                               break;
            case CL_INVALID_PLATFORM                            : std::cerr << "Invalid Platform";                                  break;
            case CL_INVALID_DEVICE                              : std::cerr << "Invalid Device";                                    break;
            case CL_INVALID_CONTEXT                             : std::cerr << "Invalid Context";                                   break;
            case CL_INVALID_QUEUE_PROPERTIES                    : std::cerr << "Invalid Queue Properties";                          break;
            case CL_INVALID_COMMAND_QUEUE                       : std::cerr << "Invalid Command Queue";                             break;
            case CL_INVALID_HOST_PTR                            : std::cerr << "Invalid Host Pointer";                              break;
            case CL_INVALID_MEM_OBJECT                          : std::cerr << "Invalid Memory Object";                             break;
            case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR             : std::cerr << "Invalid Image Format Descriptor";                   break;
            case CL_INVALID_IMAGE_SIZE                          : std::cerr << "Invalid Image Size";                                break;
            case CL_INVALID_SAMPLER                             : std::cerr << "Invalid Sampler";                                   break;
            case CL_INVALID_BINARY                              : std::cerr << "Invalid Binary";                                    break;
            case CL_INVALID_BUILD_OPTIONS                       : std::cerr << "Invalid Build Options";                             break;
            case CL_INVALID_PROGRAM                             : std::cerr << "Invalid Program";                                   break;
            case CL_INVALID_PROGRAM_EXECUTABLE                  : std::cerr << "Invalid Program Executable";                        break;
            case CL_INVALID_KERNEL_NAME                         : std::cerr << "Invalid Kernel Name";                               break;
            case CL_INVALID_KERNEL_DEFINITION                   : std::cerr << "Invalid Kernel Definition";                         break;
            case CL_INVALID_KERNEL                              : std::cerr << "Invalid Kernel";                                    break;
            case CL_INVALID_ARG_INDEX                           : std::cerr << "Invalid Argument Index";                            break;
            case CL_INVALID_ARG_VALUE                           : std::cerr << "Invalid Argument Value";                            break;
            case CL_INVALID_ARG_SIZE                            : std::cerr << "Invalid Argument Size";                             break;
            case CL_INVALID_KERNEL_ARGS                         : std::cerr << "Invalid Kernel Arguments";                          break;
            case CL_INVALID_WORK_DIMENSION                      : std::cerr << "Invalid Work Dimension";                            break;
            case CL_INVALID_WORK_GROUP_SIZE                     : std::cerr << "Invalid Workgroup Size";                            break;
            case CL_INVALID_WORK_ITEM_SIZE                      : std::cerr << "Invalid Work Item Size";                            break;
            case CL_INVALID_GLOBAL_OFFSET                       : std::cerr << "Invalid Global Offset";                             break;
            case CL_INVALID_EVENT_WAIT_LIST                     : std::cerr << "Invalid Event Wait List";                           break;
            case CL_INVALID_EVENT                               : std::cerr << "Invalid Event";                                     break;
            case CL_INVALID_OPERATION                           : std::cerr << "Invalid Operation";                                 break;
            case CL_INVALID_GL_OBJECT                           : std::cerr << "Invalid GL Object";                                 break;
            case CL_INVALID_BUFFER_SIZE                         : std::cerr << "Invalid Buffer Size";                               break;
            case CL_INVALID_MIP_LEVEL                           : std::cerr << "Invalid MIP Level";                                 break;
            case CL_INVALID_GLOBAL_WORK_SIZE                    : std::cerr << "Invalid Global Work Size";                          break;
            case CL_INVALID_PROPERTY                            : std::cerr << "Invalid Property";                                  break;

                // Requires OpenCL 1.1 (Rev33)
                //case CL_INVALID_IMAGE_DESCRIPTOR                    : std::cerr << "Invalid Image Descriptor";                          break;
                //case CL_INVALID_COMPILER_OPTIONS                    : std::cerr << "Invalid Compiler Options";                          break;
                //case CL_INVALID_LINKER_OPTIONS                      : std::cerr << "Invalid Linker Options";                            break;
                //case CL_INVALID_DEVICE_PARTITION_COUNT              : std::cerr << "Invalid Device Partition Count";                    break;

            default                                             : std::cerr << "Unhandled Error";                                   break;
        }   return exception.err(); // Return the Error Code
    }
}

#endif
