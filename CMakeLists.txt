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

file(COPY "small3d/resources" DESTINATION "./bin")

subdirs(small3d)

find_package(GLFW REQUIRED)

if(NOT WIN32)
  find_package(BZip2 REQUIRED)
endif(NOT WIN32)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PNG REQUIRED)
find_package(GLM)
find_package(OGG REQUIRED)
find_package(VORBIS REQUIRED)
find_package(Portaudio REQUIRED)
find_package(Freetype REQUIRED)
