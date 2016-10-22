small3d changelog
=======================================================

[small3d](https://github.com/dimi309/small3d)'s latest changes are listed below. The source code is always available on [GitHub](https://github.com/dimi309/small3d).

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
