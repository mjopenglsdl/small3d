project(small3dTest)
cmake_minimum_required(VERSION 3.0.0)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if(CMAKE_COMPILER_IS_GNUCXX)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
endif(CMAKE_COMPILER_IS_GNUCXX)

add_executable(test_small3d main.cpp)

target_link_libraries(test_small3d ${CONAN_LIBS})

set_target_properties(test_small3d PROPERTIES LINK_FLAGS "${CONAN_EXE_LINKER_FLAGS}")
