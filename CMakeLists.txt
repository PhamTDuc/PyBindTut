cmake_minimum_required(VERSION 3.1)
project(module_local VERSION 1.0)

# find_package(PythonInterp REQUIRED)
# include_directories(${PYTHON_INCLUDE_DIRS})


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/External/pybind11)



# find_package(PythonInterp REQUIRED)
# include_directories(${PYTHON_INCLUDE_DIRS})
# pybind11_add_module(dog ${CMAKE_CURRENT_SOURCE_DIR}/Src/module_local07Dog.cpp)
pybind11_add_module(exception_handle ${CMAKE_CURRENT_SOURCE_DIR}/Src/exception_handle08.cpp)