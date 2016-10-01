project(small3dTest)
cmake_minimum_required(VERSION 3.0.0)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_C_FLAGS "${CONAN_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CONAN_CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CONAN_SHARED_LINKER_FLAGS}")

add_executable(test_small3d main.cpp)

target_link_libraries(test_small3d ${CONAN_LIBS})

SET_TARGET_PROPERTIES(test_small3d PROPERTIES LINK_FLAGS "${CONAN_EXE_LINKER_FLAGS}")