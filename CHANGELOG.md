small3d changelog
=================

[small3d](https://github.com/dimi309/small3d)'s latest changes are listed below. The source code is always available on [GitHub](https://github.com/dimi309/small3d).

v1.2.1
------
(still open)

- Various bug fixes and code improvements.
- [BREAKING] The Renderer and SoundPlayer classes are now singletons.
- [BREAKING] Conan packaging configuration re-introduced. I will no longer be maintaining builds that don't use conan. Conan saves time.
- [BREAKING] The Exception class has been removed. Now using std::runtime_error instead.

v1.2.0
------

- Conan and cppan packaging configuration files have been removed from the repository. The conan configuration has been moved to the [repository containing my other conan contributions](https://github.com/dimi309/conan-packages).
- The documentation has been reorganised into a single README file.
- The tutorial that was part of the README file has been moved to [its own repository](https://github.com/dimi309/small3d-tutorial), together with the sample games.
- [BREAKING] Dropped support for SDL. Only using GLFW now. (I've changed my mind about keeping SDL since v1.1.0. Sorry...)
- Bug fixes and improvements for cross-platform compilation. Tested on Windows, MacOS, Debian and Fedora.
- Improvement of "manual" building instructions.

v1.1.1
------

- No breaking changes!
- Added support for GLFW. It is supported on all platforms by the independent build and on Windows when building with conan (I have not managed to successfully test a conan GLFW package that works on Linux or MacOS, at least for the moment).
- Improvement in the way memory is allocated for text rendering, thus avoiding some occasional segmentation faults on Windows.
- Improvement of the documentation for building the engine without a package manager. Check out the updated [instructions](https://github.com/dimi309/small3d/blob/master/BUILDING.md). Also, each of the branches of the [Avoid the Bug](https://github.com/dimi309/AvoidTheBug3D) game's repository is now an example of a way the game engine can be deployed and used (with SDL or GLFW, with or without conan, as well as with cppan).

v1.1.0
------

Note: I have mentioned something on Twitter about switching to GLFW and stopping to use SDL. I've decided not to do that after all. In the future, small3d may support GLFW in addition to SDL, but SDL support will not be dropped. Other than that, changes in this version reflect the intention to keep small3d small and easy to understand. Another goal is for small3d to run on as many different platforms as possible, without imposing the requirement to have the latest and greatest technology.

- Now also supporting Fedora. Instructions have been updated accordingly for the independent build and conan builds have been tested too.
- Stopped using SDL2_ttf. Now accessing freetype directly.
- [BREAKING] Renderer.render function that renders text, now takes a glm::vec3 parameter for the colour, instead of a glm::uvec4. Each component has to be a float between 0.0 and 1.0.
- [BREAKING] Renderer.render function that renders text has also been renamed to Renderer.write and its parameters have been reordered for consistency.
- [BREAKING] Renderer.getTextureHandle is now private.
- [BREAKING] Renderer.render function that renders textures has been renamed to Renderer.renderTexture and its parameters have been reordered for consistency.
- Removed ModelLoader virtual class.

v1.0.11
-------

- Corrected data type mismatches reported by compiler warnings.
- Added workaround to avoid corruption of mesh data on OpenGL 2.1.

v1.0.10
-------

- Various corrections and improvements
- [BREAKING] Renamed Renderer.clear(SceneObject) to Renderer.clearBuffers(SceneObject).
- [BREAKING] Renamed SoundPlayer.deleteSound to SoundPlayer.clear.
- [BREAKING] Needless offset parameter removed from Renderer surface rendering function.
- The colour with which to clear the screen can now optionally be set by a parameter to the Renderer.clearScreen function.

v1.0.9
------

- Complete correction of the collision detection system. Even though it had been greatly improved, it was still missing collisions. The reason was that it was performing an AABB check for each bounding box associated with each object. By translating the point with which collision is checked to the "bounding box coordinate space", this is no longer the case and collision detection has become very accurate.
- Correction of transparency problems. Images containing transparency information can now be correctly loaded and rendered.
- Corrected shader compilation error reporting.
- [BREAKING] Renamed "Sound" class to "SoundPlayer", in order to better represent what it is.

v1.0.8
------

- As usual, various bug fixes.
- Auto-replay is now supported for sounds. 
- Sounds can now be stopped before they finish playing.
- [BREAKING] Most sound manipulation functions now also take a sound handle parameter, in addition to the sound name parameter. This helps play a sound multiple times in parallel. 

v1.0.7
------
Another bug fix release.

- Corrected text rendering bug.
- [BREAKING] Textured quads and text now rendered using clear "bottom left" and "top right" parameters. The ordering of the coordinates has changed for the text rendering function.

v1.0.6
------

This is a bug fix release.

- [BREAKING] The Renderer.render function which draws a textured quad has had the array of vertex coordinates removed from its parameters and now takes two diagonally opposed corners of the quad as parameters, for simplicity.
- Many corrections made to the collision detection system.
- In order to assist in debugging collisions, an option to render associated bounding boxes when drawing a model has been added to the Renderer.render function.
- Resolved the full screen mode issue in MS Windows. Games running on small3d in full screen mode are no longer "cropped".

v1.0.5 (October 2016)
---------------------

- Lots of dynamic memory allocations removed
- [BREAKING] Model rotation, offset and speed are no longer pointers
- Comments review and improvement
- [BREAKING] Renderer init function now hidden. All initialisation happens via the constructor.
- [BREAKING] Renderer functions renderSceneObject and renderImage have been renamed to two overloaded functions, called "render".
- [BREAKING] The Text class has been removed and its functionality has been moved to another overloaded function in the Renderer, called "render".
- [BREAKING] SceneObjects passed to the new Renderer.render function are no longer enclosed in a shared_ptr, but simply passed by reference.
- [BREAKING] SceneObject.collidesWithSceneObject no longer takes a pointer, but a SceneObject, by reference, as parameter.
- [BREAKING] SceneObject.collidesWithSceneObject and SceneObject.collidesWithPoint have been renamed to two overloaded functions, called "collidesWith".
- Corrections to the documentation and introduction of automatic documentation generation, using [codedocs](https://codedocs.xyz/dimi309/small3d/annotated.html)
- [BREAKING] Renamed BoundingBoxes class to BoundingBoxSet
- [BREAKING] Renamed BoundingBoxes (now BoungingBoxSet) functions boxesAreWithin and pointIsWithin to collidesWith (overloaded).
- [BREAKING] Replaced 3 parameters which represented a point's coordinates in SceneObject.collidesWith and BoundingBoxSet.collidesWith with a single glm::vec3 parameter.
- [BREAKING] The SDL colour parameter in the Renderer.render has been replaced by a glm::uvec4
- [BREAKING] The Renderer.render method for text has had its four individual parameters, indicating the coordinates of the top left and the bottom right corner of the rectangle in which the text will be displayed, replaced by two 2-dimensional glm vectors.
- [BREAKING] The rotation logic of the camera and the models has been corrected in the source, as well as the shaders. There were many mistakes and erroneous hacks implemented up to now, because the whole logic was made to accommodate the orientation of the 3D models used for the sample games, rather than conform to a default coordinate system that a programmer could easily understand. A rotation adjustment property has also been added to the SceneObject class (and the corresponding BoundingBoxSet for collision detection), allowing for a fixed adjustment of the objects' orientation in the future, if their meshes are not facing a direction that fits in intuitively with the coordinates of the scene.
- [BREAKING] The Renderer constructor will default to full screen mode if the screen resolution is not set. There is no longer a fullScreen parameter.
- If no sound device is detected, the engine will no longer crash, but will just continue functioning, without sound.
