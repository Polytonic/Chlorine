cmake_minimum_required(VERSION 3.0)
project(Tests)

find_package(OpenCL REQUIRED)



file(GLOB TEST_KERNELS **/*.cl)
# file(COPY ${TEST_KERNELS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${TEST_KERNELS} ${CMAKE_CURRENT_BINARY_DIR}
    MAIN_DEPENDENCY ${TEST_KERNELS})

include_directories(../chlorine/include catch/include ${OpenCL_INCLUDE_DIR})
add_executable(tests test_main.cpp)
target_link_libraries(tests ${OpenCL_LIBRARY})
