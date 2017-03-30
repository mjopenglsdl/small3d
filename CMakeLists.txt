cmake_minimum_required(VERSION 3.0.2)

project(small3d)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  #Uncomment for very strict warning messages
  #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -pedantic")
endif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")

file(COPY "small3d/include" DESTINATION ".")
file(COPY "small3d/resources" DESTINATION "./bin")

if(DEFINED WITH_GLFW AND WITH_GLFW)
  add_definitions(-DSMALL3D_GLFW)
endif(DEFINED WITH_GLFW AND WITH_GLFW)

if(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)
  
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
  subdirs(small3d)

else(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${small3d_BINARY_DIR}/bin")
  if(WIN32 AND NOT MINGW)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${small3d_BINARY_DIR}/bin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${small3d_BINARY_DIR}/bin")
  endif(WIN32 AND NOT MINGW)

  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${small3d_BINARY_DIR}/lib")
  if(WIN32 AND NOT MINGW)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${small3d_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${small3d_BINARY_DIR}/lib")
  endif(WIN32 AND NOT MINGW)

  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${small3d_BINARY_DIR}/lib")
  if(WIN32 AND NOT MINGW)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${small3d_BINARY_DIR}/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${small3d_BINARY_DIR}/lib")
  endif(WIN32 AND NOT MINGW)

  if(NOT UNIX OR APPLE)
    file(COPY "deps/include" DESTINATION ".")
    file(COPY "deps/lib" DESTINATION ".")
    if(NOT APPLE)
      file(COPY "deps/bin" DESTINATION ".")
    endif(NOT APPLE)
  endif(NOT UNIX OR APPLE)

  subdirs(small3d)
  if (APPLE OR WIN32)
    set(DEPS_PATH "${CMAKE_SOURCE_DIR}/deps")
    set(CMAKE_PREFIX_PATH ${DEPS_PATH})
    if (APPLE)
      set(GLEW_LIBRARY "${DEPS_PATH}/lib/libGLEW.a")
    endif ()
  endif ()

  set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
  
  if(DEFINED WITH_GLFW AND WITH_GLFW)
    find_package(GLFW REQUIRED)
  else()
    find_package(SDL2 REQUIRED)
  endif()

  if(NOT WIN32)
    find_package(BZip2 REQUIRED)
  endif(NOT WIN32)
  
  find_package(OpenGL REQUIRED)
  find_package(GLEW REQUIRED)
  find_package(PNG REQUIRED)
  find_package(GLM)
  find_package(OGG REQUIRED)
  find_package(VORBIS REQUIRED)
  find_package(PORTAUDIO REQUIRED)
  find_package(Freetype REQUIRED)

endif(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)
