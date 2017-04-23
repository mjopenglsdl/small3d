add_library(small3d BoundingBoxSet.cpp Exception.cpp GetTokens.cpp
  Image.cpp Logger.cpp MathFunctions.cpp Model.cpp
  Renderer.cpp SceneObject.cpp
  WavefrontLoader.cpp SoundPlayer.cpp ../include/small3d/BoundingBoxSet.hpp
  ../include/small3d/Exception.hpp ../include/small3d/GetTokens.hpp ../include/small3d/Image.hpp
  ../include/small3d/Logger.hpp ../include/small3d/MathFunctions.hpp ../include/small3d/Model.hpp
  ../include/small3d/Renderer.hpp ../include/small3d/SceneObject.hpp
  ../include/small3d/SoundPlayer.hpp ../include/small3d/SoundData.hpp ../include/small3d/WavefrontLoader.hpp)

target_include_directories(small3d PUBLIC "${small3d_SOURCE_DIR}/small3d/include/small3d")

if(WIN32 AND NOT MINGW)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
  set_target_properties(small3d PROPERTIES LINK_FLAGS "/NODEFAULTLIB:\"LIBCMTD\" /NODEFAULTLIB:\"LIBCMT\"")

elseif(APPLE)

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

elseif(UNIX AND NOT APPLE)

  target_compile_options(small3d PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Avoid gcc problems in Ubuntu
  target_link_libraries(small3d PUBLIC "-ljack -lasound")

endif(WIN32 AND NOT MINGW)

include_directories(
  ${GLFW_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${PNG_INCLUDE_DIRS}
  ${GLM_INCLUDE_DIRS}
  ${OGG_INCLUDE_DIRS}
  ${VORBIS_INCLUDE_DIR}
  ${PORTAUDIO_INCLUDE_DIRS}
  ${FREETYPE_INCLUDE_DIRS}
  ${BZIP2_INCLUDE_DIRS}
  )

add_definitions(${PNG_DEFINITIONS})

target_link_libraries(small3d PUBLIC
  ${OPENGL_LIBRARIES}
  ${GLFW_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${PNG_LIBRARIES}
  ${OGG_LIBRARIES}
  ${VORBIS_LIBRARIES}
  ${PORTAUDIO_LIBRARIES}
  ${FREETYPE_LIBRARIES}    
  )

if(NOT WIN32)
  target_link_libraries(small3d PUBLIC ${BZIP2_LIBRARIES})
endif(NOT WIN32)          

# Unit testing

add_executable(small3dTest main.cpp)

target_include_directories(small3dTest PUBLIC "${small3d_SOURCE_DIR}/small3d/include")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(small3dTest PUBLIC ${GTEST_BOTH_LIBRARIES} small3d )

if(APPLE)

  set(SMALL3DTEST_LINK_FLAGS "-framework AudioUnit -framework AudioToolbox -framework CoreAudio -framework Cocoa -framework IOKit -framework CoreVideo")

  set_target_properties(small3dTest PROPERTIES LINK_FLAGS "${SMALL3DTEST_LINK_FLAGS}")

endif(APPLE)
