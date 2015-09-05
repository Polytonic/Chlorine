cmake_minimum_required(VERSION 3.1)
project(Chlorine)

# Set Compiler Flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++1y")
endif()

# Enable Coverage on Travis Tests
if(DEFINED ENV{TRAVIS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

find_package(Doxygen)
find_package(OpenCL REQUIRED)
include_directories(chlorine/include ${OpenCL_INCLUDE_DIR})
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
add_executable(tests EXCLUDE_FROM_ALL tests/test_suite.hpp tests/test_main.cpp ${TEST_KERNELS})
target_link_libraries(tests ${OpenCL_LIBRARY})
add_custom_command(TARGET tests PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/tests/kernels/
                   $<TARGET_FILE_DIR:tests>/kernels/)

# Workaround for Reserved CMAKE Keyword: test
add_custom_target(check COMMAND tests --reporter compact DEPENDS tests)

# Build the Examples
add_subdirectory(examples/swap EXCLUDE_FROM_ALL)
add_subdirectory(examples/mandelbrot EXCLUDE_FROM_ALL)

# Build the Documentation
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/.doxyfile
                   ${CMAKE_CURRENT_BINARY_DIR}/.doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE}
                      ${CMAKE_CURRENT_BINARY_DIR}/.doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
endif(DOXYGEN_FOUND)
