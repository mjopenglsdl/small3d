add_library(small3d BoundingBoxSet.cpp GetTokens.cpp Image.cpp Logger.cpp Model.cpp OpenGL/Renderer.cpp
  SceneObject.cpp Sound.cpp ../include/small3d/BoundingBoxSet.hpp
  ../include/small3d/GetTokens.hpp ../include/small3d/Image.hpp ../include/small3d/Logger.hpp
  ../include/small3d/Model.hpp ../include/small3d/OpenGL/Renderer.hpp ../include/small3d/SceneObject.hpp
  ../include/small3d/Sound.hpp)

target_include_directories(small3d PUBLIC "${small3d_SOURCE_DIR}/small3d/include/small3d")
target_include_directories(small3d PUBLIC "${small3d_SOURCE_DIR}/small3d/include/small3d/OpenGL")

if(MINGW)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif(MINGW)

message(STATUS "cpp flags: ${CMAKE_CXX_FLAGS}")

if(DEFINED BUILD_TESTS AND BUILD_TESTS)
  add_executable(unittests unit_tests.cpp)
  file(COPY "${small3d_SOURCE_DIR}/small3d/resources" DESTINATION "${small3d_BINARY_DIR}/bin")
  target_include_directories(unittests PUBLIC "${small3d_SOURCE_DIR}/small3d/include")
  target_link_libraries(unittests PUBLIC small3d "${CONAN_LIBS}")
  set_target_properties(unittests PROPERTIES LINK_FLAGS "${CONAN_EXE_LINKER_FLAGS}")
  if(MSVC)
    set_target_properties(unittests PROPERTIES LINK_FLAGS_RELEASE "-NODEFAULTLIB:MSVCRTD")
    set_target_properties(unittests PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${small3d_BINARY_DIR}/bin")
  endif(MSVC)
endif(DEFINED BUILD_TESTS AND BUILD_TESTS)
