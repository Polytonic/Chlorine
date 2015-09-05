cmake_minimum_required(VERSION 3.0)
project(Swap)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++1y")
endif()

find_package(OpenCL REQUIRED)
include_directories(../../chlorine/include ${OpenCL_INCLUDE_DIR})
file(GLOB PROJECT_HEADERS *.hpp)
file(GLOB PROJECT_SOURCES *.cpp)
file(GLOB PROJECT_KERNELS *.cl)
file(GLOB PROJECT_CONFIGS readme.md)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Kernels" FILES ${PROJECT_KERNELS})

add_executable(swap ${PROJECT_HEADERS} ${PROJECT_SOURCES}
                    ${PROJECT_KERNELS} ${PROJECT_CONFIGS})
target_link_libraries(swap ${OpenCL_LIBRARY})
add_custom_command(TARGET swap PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/swap.cl
                   $<TARGET_FILE_DIR:swap>/swap.cl)
