project(GlewTest)
cmake_minimum_required(VERSION 3.0.0)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/..)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(test_small3d main.cpp)

FIND_PACKAGE(SMALL3D REQUIRED)
INCLUDE_DIRECTORIES("${SMALL3D_INCLUDE_DIRS}")
TARGET_LINK_LIBRARIES(test_small3d PUBLIC "${SMALL3D_LIBRARIES}")

