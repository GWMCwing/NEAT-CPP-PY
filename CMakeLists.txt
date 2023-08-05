cmake_minimum_required(VERSION 3.12)
project(neatcpy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the paths for your source, include, and pybind11 directories
# set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/NEAT)
# set(PYBIND11_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11)
set(SOURCE_DIR src)
set(INCLUDE_DIR include/NEAT)
set(PYBIND11_DIR lib/pybind11)

find_package(Python COMPONENTS Interpreter Development REQUIRED)
# find_package(pybind11 CONFIG REQUIRED)
# find_package(Python 3.6 COMPONENTS Interpreter Development REQUIRED)

# Add the pybind11 module
add_subdirectory(${PYBIND11_DIR})

# Create the target for your binding
file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
# pybind11_add_module(neatcpy ${SOURCE_DIR}/_Python_lib.cpp)
# pybind11_add_module(neatcpy ${SOURCE_FILES} )
python_add_library(_neatcpy MODULE ${SOURCE_FILES})
# target_link_libraries(neatcpy PRIVATE pybind11::headers)


# Set the include directories for your project
# target_include_directories(neatcpy PRIVATE ${INCLUDE_DIR})
target_compile_definitions(_neatcpy PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
# Add any additional libraries or dependencies as needed
# target_link_libraries(neatcpy PRIVATE <library_name>)
# Set the output directory for the generated binding
# set_target_properties(neatcpy PROPERTIES LIBRARY_OUTPUT_DIRECTORY bin)

install(TARGETS _neatcpy DESTINATION neatcpy)
