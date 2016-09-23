ADD_EXECUTABLE(avoidthebug3d avoidthebug3d.cpp GameLogic.cpp)
TARGET_INCLUDE_DIRECTORIES(avoidthebug3d PUBLIC "${game_SOURCE_DIR}/include")
TARGET_LINK_LIBRARIES(avoidthebug3d PUBLIC "${CONAN_LIBS}")

IF(APPLE)
  TARGET_LINK_LIBRARIES(avoidthebug3d PUBLIC "-framework OpenGL")
ELSEIF(UNIX)
  TARGET_LINK_LIBRARIES(avoidthebug3d PUBLIC "-lasound")
ENDIF()

IF(NOT WIN32 OR MINGW)
  IF(APPLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
  ELSE()
    target_compile_options(avoidthebug3d PUBLIC "-std=c++11" "-Wl,--no-as-needed") 
  ENDIF()
ENDIF()

