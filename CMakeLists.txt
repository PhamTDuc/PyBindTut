cmake_minimum_required(VERSION 3.1)
project(functions VERSION 1.0)

find_package(PythonInterp REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/External/pybind11)
# pybind11_add_module(sample ${CMAKE_CURRENT_SOURCE_DIR}/Src/sample.cpp)
# pybind11_add_module(policies ${CMAKE_CURRENT_SOURCE_DIR}/Src/policies.cpp)
pybind11_add_module(functions ${CMAKE_CURRENT_SOURCE_DIR}/Src/functions.cpp)