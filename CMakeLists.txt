cmake_minimum_required(VERSION 3.12)
project(NEAT-CPP-PY)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the paths for your source, include, and pybind11 directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/NEAT)
set(PYBIND11_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11)

# Add the pybind11 module
add_subdirectory(${PYBIND11_DIR})

# Create the target for your binding
file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
# pybind11_add_module(NEATCPP ${SOURCE_DIR}/_Python_lib.cpp)
pybind11_add_module(NEATCPP ${SOURCE_FILES})

# Set the include directories for your project
target_include_directories(NEATCPP PRIVATE ${INCLUDE_DIR})

# Add any additional libraries or dependencies as needed
# target_link_libraries(NEATCPP PRIVATE <library_name>)
# Set the output directory for the generated binding
set_target_properties(NEATCPP PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)