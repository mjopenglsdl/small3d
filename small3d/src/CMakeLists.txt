ADD_LIBRARY(small3d BoundingBoxSet.cpp Exception.cpp GetTokens.cpp
      Image.cpp Logger.cpp MathFunctions.cpp Model.cpp
      ModelLoader.cpp Renderer.cpp SceneObject.cpp
      WavefrontLoader.cpp SoundPlayer.cpp ../include/small3d/BoundingBoxSet.hpp
    ../include/small3d/Exception.hpp ../include/small3d/GetTokens.hpp ../include/small3d/Image.hpp
    ../include/small3d/Logger.hpp ../include/small3d/MathFunctions.hpp ../include/small3d/Model.hpp
    ../include/small3d/ModelLoader.hpp ../include/small3d/Renderer.hpp ../include/small3d/SceneObject.hpp
    ../include/small3d/SoundPlayer.hpp ../include/small3d/SoundData.hpp ../include/small3d/WavefrontLoader.hpp)

TARGET_INCLUDE_DIRECTORIES(small3d PUBLIC "${small3d_SOURCE_DIR}/small3d/include/small3d")

IF(NOT WIN32 OR MINGW)
  IF(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
  ELSE()
    target_compile_options(small3d PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Avoid gcc problems in Ubuntu
  ENDIF()
ELSE()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
ENDIF()

IF(APPLE)
  SET_TARGET_PROPERTIES(small3d PROPERTIES LINK_FLAGS
      "-framework AudioUnit AudioToolbox CoreAudio")
ELSEIF(WIN32 AND NOT MINGW)
  SET_TARGET_PROPERTIES(small3d PROPERTIES LINK_FLAGS
    "/NODEFAULTLIB:\"LIBCMTD\" /NODEFAULTLIB:\"LIBCMT\"")
ELSE()
  TARGET_LINK_LIBRARIES(small3d PUBLIC "-ljack -lasound")
ENDIF()

IF(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)

  set(CMAKE_C_FLAGS "${CONAN_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CONAN_CXX_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CONAN_SHARED_LINKER_FLAGS}")
  TARGET_LINK_LIBRARIES(small3d PUBLIC ${CONAN_LIBS})

ELSE()

  INCLUDE_DIRECTORIES(
      ${OPENGL_INCLUDE_DIR}
      ${SDL2_INCLUDE_DIR}
      ${GLEW_INCLUDE_DIRS}
      ${PNG_INCLUDE_DIRS}
      ${GLM_INCLUDE_DIRS}
      ${OGG_INCLUDE_DIRS}
      ${VORBIS_INCLUDE_DIR}
      ${PORTAUDIO_INCLUDE_DIRS}
      ${FREETYPE_INCLUDE_DIRS}
      ${BZIP2_INCLUDE_DIRS})

  ADD_DEFINITIONS(${PNG_DEFINITIONS})

  TARGET_LINK_LIBRARIES(small3d PUBLIC
      ${OPENGL_LIBRARIES}
      ${SDL2_LIBRARY}
      ${GLEW_LIBRARIES}
      ${PNG_LIBRARIES}
      ${OGG_LIBRARIES}
      ${VORBIS_LIBRARIES}
      ${PORTAUDIO_LIBRARIES}
      ${FREETYPE_LIBRARIES}    
      )

  IF(NOT WIN32)
    TARGET_LINK_LIBRARIES(small3d PUBLIC ${BZIP2_LIBRARIES})
  ENDIF()

  ADD_EXECUTABLE(small3dTest main.cpp)

  TARGET_INCLUDE_DIRECTORIES(small3dTest PUBLIC
      "${small3d_SOURCE_DIR}/small3d/include")

  FIND_PACKAGE(GTest REQUIRED)
  INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(small3dTest PUBLIC ${GTEST_BOTH_LIBRARIES} small3d)

ENDIF()







