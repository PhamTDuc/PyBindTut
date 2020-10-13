cmake_minimum_required(VERSION 3.1)
project(sample VERSION 1.0)

find_package(PythonInterp REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/External/pybind11)
pybind11_add_module(sample ${CMAKE_CURRENT_SOURCE_DIR}/Src/sample.cpp)