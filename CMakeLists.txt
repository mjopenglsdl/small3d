include(${CMAKE_HOME_DIRECTORY}/biicode.cmake)

# Initializes block variables
INIT_BIICODE_BLOCK()

IF(APPLE)
	SET(BII_IMPLICIT_RULES_ENABLED FALSE)
ENDIF()

# Actually create targets: EXEcutables and libraries.
ADD_BIICODE_TARGETS()

# Link OpenGL things and set to use C++11
if(NOT WIN32 OR MINGW)
	IF(APPLE)
		FIND_PACKAGE(OpenGL REQUIRED)
                INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
		TARGET_LINK_LIBRARIES(${BII_LIB_TARGET} PUBLIC ${OPENGL_LIBRARIES})
	ELSE()
		target_compile_options(${BII_LIB_TARGET} PUBLIC "-std=c++11" "-Wl,--no-as-needed") # Ubuntu if gcc problems
	ENDIF()
endif()
