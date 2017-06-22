add_library(small3d BoundingBoxSet.cpp GetTokens.cpp Image.cpp Logger.cpp MathFunctions.cpp Model.cpp
  Renderer.cpp SceneObject.cpp WavefrontLoader.cpp SoundPlayer.cpp ../include/small3d/BoundingBoxSet.hpp
  ../include/small3d/GetTokens.hpp ../include/small3d/Image.hpp ../include/small3d/Logger.hpp
  ../include/small3d/MathFunctions.hpp ../include/small3d/Model.hpp ../include/small3d/Renderer.hpp
  ../include/small3d/SceneObject.hpp ../include/small3d/SoundPlayer.hpp ../include/small3d/SoundData.hpp
  ../include/small3d/WavefrontLoader.hpp)

target_include_directories(small3d PUBLIC "${small3d_SOURCE_DIR}/small3d/include/small3d")

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif(MSVC)
