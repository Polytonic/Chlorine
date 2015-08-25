cmake_minimum_required(VERSION 3.0)
project(Chlorine)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++1y")
endif()

find_package(OpenCL REQUIRED)
include_directories(chlorine/include)
file(GLOB PROJECT_HEADERS chlorine/include/*.hpp)
file(GLOB PROJECT_SOURCES chlorine/src/*.cpp)
file(GLOB PROJECT_CONFIGS readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

# Build the Chlorine CLI
add_executable(chlorine ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_CONFIGS})
target_link_libraries(chlorine ${OpenCL_LIBRARY})

# Build the clinfo Helper
add_executable(clinfo chlorine/include/cl.hpp chlorine/clinfo/clinfo.cpp)
target_link_libraries(clinfo ${OpenCL_LIBRARY})

# Build the Test Suite
include_directories(tests tests/catch/include)
file(GLOB TEST_KERNELS tests/**/*.cl)
source_group("Kernels" FILES ${TEST_KERNELS})
add_executable(check tests/test_suite.hpp tests/test_main.cpp ${TEST_KERNELS})
target_link_libraries(check ${OpenCL_LIBRARY})
add_custom_command(TARGET check PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/tests/kernels/
                   $<TARGET_FILE_DIR:check>/tests/)
