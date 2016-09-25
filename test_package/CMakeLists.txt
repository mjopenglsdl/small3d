project(small3dTest)
cmake_minimum_required(VERSION 3.0.0)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(test_small3d main.cpp)

target_link_libraries(test_small3d ${CONAN_LIBS})

if(NOT WIN32 OR MINGW)
  IF(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
  ELSE()
    target_compile_options(test_small3d PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Ubuntu if gcc problems
  ENDIF()
endif()
