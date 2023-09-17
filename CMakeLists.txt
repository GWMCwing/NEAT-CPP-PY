cmake_minimum_required(VERSION 3.4...3.18)
# project(cmake_example)
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

# add_subdirectory(lib/pybind11)
file(GLOB SOURCE_FILES src/*.cpp)
python_add_library(_neatcpy MODULE ${SOURCE_FILES} WITH_SOABI)
target_link_libraries(_neatcpy PRIVATE pybind11::headers)
target_compile_definitions(_neatcpy PRIVATE VERSION_INFO=${PROJECT_VERSION})

install(TARGETS _neatcpy DESTINATION neatcpy)
