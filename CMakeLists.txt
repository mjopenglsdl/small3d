cmake_minimum_required(VERSION 3.0.2)

project(small3d)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
if(CMAKE_COMPILER_IS_GNUCXX)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  #Uncomment for very strict warning messages
  #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -pedantic")
endif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")

subdirs(small3d)
