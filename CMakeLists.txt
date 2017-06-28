cmake_minimum_required(VERSION 3.0.2)

project(small3d)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

subdirs(small3d)
