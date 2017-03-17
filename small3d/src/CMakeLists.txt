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

if(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)

  set(CMAKE_C_FLAGS "${CONAN_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CONAN_CXX_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CONAN_SHARED_LINKER_FLAGS}")
  target_link_libraries(small3d PUBLIC ${CONAN_LIBS})

else(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)

  if(DEFINED WITH_GLFW AND WITH_GLFW)
    include_directories(${GLFW_INCLUDE_DIRS})
    target_link_libraries(small3d PUBLIC ${GLFW_LIBRARIES})
  else()
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(small3d PUBLIC ${SDL2_LIBRARY})
  endif()

  include_directories(
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
  
endif(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN)

# Unit testing

if(DEFINED BUILD_UNIT_TESTS AND BUILD_UNIT_TESTS)

  if(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN AND(APPLE OR WIN32))
    set(DEPS_PATH "${CMAKE_SOURCE_DIR}/deps")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${DEPS_PATH}")
  endif(DEFINED BUILD_WITH_CONAN AND BUILD_WITH_CONAN AND(APPLE OR WIN32))
  
  add_executable(small3dTest main.cpp)

  target_include_directories(small3dTest PUBLIC "${small3d_SOURCE_DIR}/small3d/include")

  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
  target_link_libraries(small3dTest PUBLIC ${GTEST_BOTH_LIBRARIES} small3d )
  
  if(APPLE)

    set(SMALL3DTEST_LINK_FLAGS "-framework AudioUnit -framework AudioToolbox -framework CoreAudio")

    if(DEFINED WITH_GLFW AND WITH_GLFW)
      set(SMALL3DTEST_LINK_FLAGS "${SMALL3DTEST_LINK_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo")
    endif()

    set_target_properties(small3dTest PROPERTIES LINK_FLAGS "${SMALL3DTEST_LINK_FLAGS}")

  endif(APPLE)

endif(DEFINED BUILD_UNIT_TESTS AND BUILD_UNIT_TESTS)
