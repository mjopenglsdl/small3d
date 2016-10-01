ADD_LIBRARY(small3d BoundingBoxSet.cpp Exception.cpp GetTokens.cpp
      Image.cpp Logger.cpp MathFunctions.cpp Model.cpp
      ModelLoader.cpp Renderer.cpp SceneObject.cpp
      WavefrontLoader.cpp SoundData.cpp Sound.cpp ../include/small3d/BoundingBoxSet.hpp
    ../include/small3d/Exception.hpp ../include/small3d/GetTokens.hpp ../include/small3d/Image.hpp
    ../include/small3d/Logger.hpp ../include/small3d/MathFunctions.hpp ../include/small3d/Model.hpp
    ../include/small3d/ModelLoader.hpp ../include/small3d/Renderer.hpp ../include/small3d/SceneObject.hpp
    ../include/small3d/Sound.hpp ../include/small3d/SoundData.hpp ../include/small3d/WavefrontLoader.hpp)

IF(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)
  TARGET_COMPILE_DEFINITIONS(small3d PUBLIC "${CONAN_DEFINES}")
  TARGET_LINK_LIBRARIES(small3d PUBLIC ${CONAN_LIBS})
ELSE()
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} ${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS}
  	${PNG_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${OGG_INCLUDE_DIRS} ${VORBIS_INCLUDE_DIR} ${PORTAUDIO_INCLUDE_DIRS})
  ADD_DEFINITIONS(${PNG_DEFINITIONS})
  TARGET_LINK_LIBRARIES(small3d PUBLIC ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES}
  	${GLEW_LIBRARIES} ${PNG_LIBRARIES} ${OGG_LIBRARIES} ${VORBIS_LIBRARIES} ${PORTAUDIO_LIBRARIES})

  ADD_EXECUTABLE(small3dTest main.cpp)

  TARGET_INCLUDE_DIRECTORIES(small3dTest PUBLIC "${small3d_SOURCE_DIR}/small3d/include")

  FIND_PACKAGE(GTest REQUIRED)
  INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(small3dTest PUBLIC ${GTEST_BOTH_LIBRARIES})

  TARGET_LINK_LIBRARIES(small3dTest PUBLIC small3d)

ENDIF()

IF(APPLE)
  FIND_LIBRARY(AUDIOUNIT_LIBRARY AudioUnit)
  FIND_LIBRARY(AUDIOTOOLBOX_LIBRARY AudioToolbox)
  FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
  TARGET_LINK_LIBRARIES(small3d PUBLIC ${COREAUDIO_LIBRARY} ${AUDIOUNIT_LIBRARY} ${AUDIOTOOLBOX_LIBRARY})
ENDIF(APPLE)


TARGET_INCLUDE_DIRECTORIES(small3d PUBLIC "${small3d_SOURCE_DIR}/small3d/include/small3d")

if(NOT WIN32 OR MINGW)
  IF(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
  ELSE()
    target_compile_options(small3d PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Ubuntu if gcc problems
  ENDIF()
endif()

IF(WIN32 AND NOT MINGW)
  SET_TARGET_PROPERTIES(small3d PROPERTIES LINK_FLAGS "/NODEFAULTLIB:\"LIBCMTD\" /NODEFAULTLIB:\"LIBCMT\"")
ENDIF()
