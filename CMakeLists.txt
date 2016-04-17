CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(small3d)

ADD_LIBRARY(small3d BoundingBoxes.cpp BoundingBoxes.hpp Exception.cpp Exception.hpp GetTokens.cpp GetTokens.hpp
        Image.cpp Image.hpp Logger.cpp Logger.hpp MathFunctions.cpp MathFunctions.hpp Model.cpp Model.hpp
        ModelLoader.cpp ModelLoader.hpp Renderer.cpp Renderer.hpp SceneObject.cpp SceneObject.hpp Text.cpp
        Text.hpp WavefrontLoader.cpp WavefrontLoader.hpp)

ADD_EXECUTABLE(small3dTest main.cpp)

# Link OpenGL things and set to use C++11
if(NOT WIN32 OR MINGW)
  IF(APPLE)
    FIND_PACKAGE(OpenGL REQUIRED)
    INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    TARGET_LINK_LIBRARIES(small3d PUBLIC ${OPENGL_LIBRARIES})
  ELSE()
    target_compile_options(small3d PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Ubuntu if gcc problems
  ENDIF()
endif()

SET(DEPS_PATH "${CMAKE_SOURCE_DIR}/deps")
SET(CMAKE_PREFIX_PATH ${DEPS_PATH})
SET(SDL_LIBRARY_TEMP "${DEPS_PATH}/SDL2.framework")
SET(SDL_TTF_LIBRARY "${DEPS_PATH}/SDL2_ttf.framework")
SET(GTEST_ROOT "${DEPS_PATH}/gtest")

FIND_PACKAGE(SDL REQUIRED)
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(small3d PUBLIC "${SDL_LIBRARY}")

FIND_PACKAGE(SDL_ttf REQUIRED)
INCLUDE_DIRECTORIES(${SDL_TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(small3d PUBLIC "${SDL_TTF_LIBRARIES}")

IF(APPLE)
    SET(GLEW_INCLUDE_DIR "${DEPS_PATH}/glew/include")
    SET(GLEW_LIBRARY "${DEPS_PATH}/glew/lib/libGLEW.a")
ENDIF()
FIND_PACKAGE(GLEW REQUIRED)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(small3d PUBLIC "${GLEW_LIBRARIES}")

#FIND_PACKAGE(ZLIB REQUIRED)

FIND_PACKAGE(PNG REQUIRED)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIRS})
ADD_DEFINITIONS(${PNG_DEFINITIONS})
TARGET_LINK_LIBRARIES(small3d PUBLIC "${PNG_LIBRARIES}")

#FIND_PACKAGE(GTEST REQUIRED)
#INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

INCLUDE_DIRECTORIES("${DEPS_PATH}/googletest/include")
TARGET_LINK_LIBRARIES(small3dTest PUBLIC "${DEPS_PATH}/googletest/libgtest.a")

IF(NOT APPLE)
    FIND_PACKAGE(GLEW REQUIRED)
ENDIF()

IF(APPLE)
    INCLUDE_DIRECTORIES("${DEPS_PATH}/include")
ENDIF()

IF(WIN32 AND NOT MINGW)
    SET_TARGET_PROPERTIES(small3d PROPERTIES LINK_FLAGS "/NODEFAULTLIB:\"LIBCMTD\" /NODEFAULTLIB:\"LIBCMT\"")
ENDIF()

TARGET_LINK_LIBRARIES(small3dTest PUBLIC small3d)

FILE(COPY "resources" DESTINATION ".")
FILE(COPY "samplegame" DESTINATION ".")

ADD_EXECUTABLE(avoidthebug3d samplegame/avoidthebug3d.cpp samplegame/GameLogic.cpp samplegame/GameLogic.hpp
        samplegame/KeyInput.hpp)
TARGET_INCLUDE_DIRECTORIES(avoidthebug3d PUBLIC ".")
TARGET_LINK_LIBRARIES(avoidthebug3d PUBLIC small3d)

FILE(COPY "samplegame/resources" DESTINATION ".")
FILE(COPY "resources/shaders" DESTINATION ".")
