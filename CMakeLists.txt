cmake_minimum_required(VERSION 3.4...3.18)
# project(cmake_example)
project(neatcpy)


add_subdirectory(lib/pybind11)
file(GLOB SOURCE_FILES src/*.cpp)
pybind11_add_module(neatcpy ${SOURCE_FILES})

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(neatcpy
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
