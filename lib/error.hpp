#ifndef CHLORINE_ERROR
#define CHLORINE_ERROR

#include <string>
#include <map>

//Checking for OpenCL 1.1 (Rev33)
//if one doesn't exist, assume that all of those from that rev don't exist?
#ifndef CL_COMPILE_PROGRAM_FAILURE
#define CL_COMPILE_PROGRAM_FAILURE ( -15 )
#define CL_LINKER_NOT_AVAILABLE ( -16 )
#define CL_DEVICE_PARTITION_FAILED ( -18 )
#define CL_KERNEL_ARG_INFO_NOT_AVAILABLE ( -19 )
#endif

//Checking for OpenCL 1.2
//error codes 65-69 are new to opencl 1.2, so if it doesn't have 65 it probably doesn't have any of the rest
#ifndef CL_INVALID_IMAGE_DESCRIPTOR
#define CL_INVALID_IMAGE_DESCRIPTOR ( -65 )
#define CL_INVALID_COMPILER_OPTIONS ( -66 )
#define CL_INVALID_LINKER_OPTIONS ( -67 )
#define CL_INVALID_DEVICE_PARTITION_COUNT ( -68 )
#endif



namespace ch
{
    // Display Additional Information About the Exception
    int print_exception_string(cl::Error exception)
    {
        fprintf(stderr, "%s (%d): ", exception.what(), exception.err());

        std::map<int, std::string> error_lookup;

        error_lookup[CL_SUCCESS] =                                   "Success";                                       
        error_lookup[CL_DEVICE_NOT_FOUND] =                          "Device Not Found";                              
        error_lookup[CL_DEVICE_NOT_AVAILABLE] =                      "Device Not Available";                          
        error_lookup[CL_COMPILER_NOT_AVAILABLE] =                    "Compiler Not Available";                        
        error_lookup[CL_MEM_OBJECT_ALLOCATION_FAILURE] =             "Memory Object Allocation Failure";              
        error_lookup[CL_OUT_OF_RESOURCES] =                          "Out of Resources";                              
        error_lookup[CL_OUT_OF_HOST_MEMORY] =                        "Out of Host Memory";                            
        error_lookup[CL_PROFILING_INFO_NOT_AVAILABLE] =              "Profiling Information Not Available";           
        error_lookup[CL_MEM_COPY_OVERLAP] =                          "Memory Copy Overlap";                           
        error_lookup[CL_IMAGE_FORMAT_MISMATCH] =                     "Image Format Mismatch";                         
        error_lookup[CL_IMAGE_FORMAT_NOT_SUPPORTED] =                "Image Format Not Supported";                    
        error_lookup[CL_BUILD_PROGRAM_FAILURE] =                     "Build Program Failure";                         
        error_lookup[CL_MAP_FAILURE] =                               "Map Failure";                                   
        error_lookup[CL_MISALIGNED_SUB_BUFFER_OFFSET] =              "Misaligned Sub-Buffer Offset";                  
        error_lookup[CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST] = "Execution Status Error for Events in Wait List";

        //Requires OpenCL 1.1 (Rev33)
        error_lookup[CL_COMPILE_PROGRAM_FAILURE] =                 "Compile Program Failure";
        error_lookup[CL_LINKER_NOT_AVAILABLE] =                    "Linker Not Available";
        error_lookup[CL_LINK_PROGRAM_FAILURE] =                    "Link Program Failure";
        error_lookup[CL_DEVICE_PARTITION_FAILED] =                 "Device Partition Failed";
        error_lookup[CL_KERNEL_ARG_INFO_NOT_AVAILABLE] =           "Kernel Argument Information Not Available";

        error_lookup[CL_INVALID_VALUE] =                             "Invalid Value";                                 
        error_lookup[CL_INVALID_DEVICE_TYPE] =                       "Invalid Device Type";                           
        error_lookup[CL_INVALID_PLATFORM] =                          "Invalid Platform";                              
        error_lookup[CL_INVALID_DEVICE] =                            "Invalid Device";                                
        error_lookup[CL_INVALID_CONTEXT] =                           "Invalid Context";                               
        error_lookup[CL_INVALID_QUEUE_PROPERTIES] =                  "Invalid Queue Properties";                      
        error_lookup[CL_INVALID_COMMAND_QUEUE] =                     "Invalid Command Queue";                         
        error_lookup[CL_INVALID_HOST_PTR] =                          "Invalid Host Pointer";                         
        error_lookup[CL_INVALID_MEM_OBJECT] =                        "Invalid Memory Object";                         
        error_lookup[CL_INVALID_IMAGE_FORMAT_DESCRIPTOR] =           "Invalid Image Format Descriptor";               
        error_lookup[CL_INVALID_IMAGE_SIZE] =                        "Invalid Image Size";                            
        error_lookup[CL_INVALID_SAMPLER] =                           "Invalid Sampler";                               
        error_lookup[CL_INVALID_BINARY] =                            "Invalid Binary";                                
        error_lookup[CL_INVALID_BUILD_OPTIONS] =                     "Invalid Build Options";                         
        error_lookup[CL_INVALID_PROGRAM] =                           "Invalid Program";                               
        error_lookup[CL_INVALID_PROGRAM_EXECUTABLE] =                "Invalid Program Executable";                    
        error_lookup[CL_INVALID_KERNEL_NAME] =                       "Invalid Kernel Name";                           
        error_lookup[CL_INVALID_KERNEL_DEFINITION] =                 "Invalid Kernel Definition";                     
        error_lookup[CL_INVALID_KERNEL] =                            "Invalid Kernel";                                
        error_lookup[CL_INVALID_ARG_INDEX] =                         "Invalid Argument Index";                        
        error_lookup[CL_INVALID_ARG_VALUE] =                         "Invalid Argument Value";                        
        error_lookup[CL_INVALID_ARG_SIZE] =                          "Invalid Argument Size";                         
        error_lookup[CL_INVALID_KERNEL_ARGS] =                       "Invalid Kernel Arguments";                      
        error_lookup[CL_INVALID_WORK_DIMENSION] =                    "Invalid Work Dimension";                        
        error_lookup[CL_INVALID_WORK_GROUP_SIZE] =                   "Invalid Workgroup Size";                        
        error_lookup[CL_INVALID_WORK_ITEM_SIZE] =                    "Invalid Work Item Size";                        
        error_lookup[CL_INVALID_GLOBAL_OFFSET] =                     "Invalid Global Offset";                         
        error_lookup[CL_INVALID_EVENT_WAIT_LIST] =                   "Invalid Event Wait List";                       
        error_lookup[CL_INVALID_EVENT] =                             "Invalid Event";                                 
        error_lookup[CL_INVALID_OPERATION] =                         "Invalid Operation";                             
        error_lookup[CL_INVALID_GL_OBJECT] =                         "Invalid GL Object";                             
        error_lookup[CL_INVALID_BUFFER_SIZE] =                       "Invalid Buffer Size";                           
        error_lookup[CL_INVALID_MIP_LEVEL] =                         "Invalid MIP Level";                             
        error_lookup[CL_INVALID_GLOBAL_WORK_SIZE] =                  "Invalid Global Work Size";                      
        error_lookup[CL_INVALID_PROPERTY] =                          "Invalid Property";                              
        
        // Requires OpenCL 1.2 (was originally stated that this was added in 1.1 but according to online this is new to 1.2?)
        error_lookup[CL_INVALID_IMAGE_DESCRIPTOR] =                   "Invalid Image Descriptor";
        error_lookup[CL_INVALID_COMPILER_OPTIONS] =                   "Invalid Compiler Options";
        error_lookup[CL_INVALID_LINKER_OPTIONS] =                     "Invalid Linker Options"; 
        error_lookup[CL_INVALID_DEVICE_PARTITION_COUNT] =             "Invalid Device Partition Count";

        if (error_lookup.find(exception.err()) != error_lookup.end()){
            std::cerr << error_lookup[exception.err()];
        }
        else{
            std::cerr << "Unhandled Error";
        }

        return exception.err(); // Return the Error Code
    }
}

#endif
