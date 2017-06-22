cmake_minimum_required(VERSION 3.0.2)
project(unit_testing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(COPY "resources" DESTINATION "./bin")

add_executable(unittests main.cpp)

target_link_libraries(unittests PUBLIC "${CONAN_LIBS}")

set_target_properties(unittests PROPERTIES LINK_FLAGS "${CONAN_EXE_LINKER_FLAGS}")

if(MSVC)
  set_target_properties(unittests PROPERTIES LINK_FLAGS_RELEASE "-NODEFAULTLIB:MSVCRTD")
  set_target_properties(unittests PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${unittests_BINARY_DIR}/bin")
endif(MSVC)
