project(GlewTest)
cmake_minimum_required(VERSION 3.0.0)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/..)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(test_small3d main.cpp)

FIND_PACKAGE(SMALL3D REQUIRED)
INCLUDE_DIRECTORIES("${SMALL3D_INCLUDE_DIRS}")
TARGET_LINK_LIBRARIES(test_small3d PUBLIC "${SMALL3D_LIBRARIES}")

if(NOT WIN32 OR MINGW)
  IF(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
  ELSE()
    target_compile_options(test_small3d PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Ubuntu if gcc problems
  ENDIF()
endif()
