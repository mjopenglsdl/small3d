add_library(small3d BoundingBoxSet.cpp GetTokens.cpp Image.cpp Logger.cpp MathFunctions.cpp Model.cpp
  Renderer.cpp SceneObject.cpp WavefrontLoader.cpp SoundPlayer.cpp ../include/small3d/BoundingBoxSet.hpp
  ../include/small3d/GetTokens.hpp ../include/small3d/Image.hpp ../include/small3d/Logger.hpp
  ../include/small3d/MathFunctions.hpp ../include/small3d/Model.hpp ../include/small3d/Renderer.hpp
  ../include/small3d/SceneObject.hpp ../include/small3d/SoundPlayer.hpp ../include/small3d/SoundData.hpp
  ../include/small3d/WavefrontLoader.hpp)

target_include_directories(small3d PUBLIC "${small3d_SOURCE_DIR}/small3d/include/small3d")

if(DEFINED BUILD_TESTS AND BUILD_TESTS)
  
  file(COPY "resources" DESTINATION "./bin")
  add_executable(unittests main.cpp)
  target_link_libraries(unittests PUBLIC small3d "${CONAN_LIBS}")
  set_target_properties(unittests PROPERTIES LINK_FLAGS "${CONAN_EXE_LINKER_FLAGS}")

  if(MSVC)
    set_target_properties(unittests PROPERTIES LINK_FLAGS_RELEASE "-NODEFAULTLIB:MSVCRTD")
    set_target_properties(unittests PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${unittests_BINARY_DIR}/bin")
  endif()
  
endif(DEFINED BUILD_TESTS AND BUILD_TESTS)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
elseif(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
elseif(UNIX AND NOT APPLE)
  target_compile_options(small3d PUBLIC "-std=c++11")
  target_compile_options(unittests PUBLIC "-std=c++11")
endif(MSVC)
