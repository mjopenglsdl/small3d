small3d changelog
=======================================================

[small3d](https://github.com/dimi309/small3d)'s latest changes are listed below. The source code is always available on [GitHub](https://github.com/dimi309/small3d).

v1.0.5
------
- Lots of dynamic memory allocations removed
- [BREAKING] Model rotation, offset and speed are no longer pointers 
- [BREAKING] Camera rotation adjustments to align it with the "character" (scene objects) rotations when following them have been moved from the sample games to the engine's source code.
- Comments overview and improvement
- [BREAKING] Renderer init function now hidden. All initialisation happens via the constructor.
- [BREAKING] Renderer functions renderSceneObject and renderImage have been renamed to two overloaded functions, called "render".
- [BREAKING] The Text class has been removed and its functionality has been moved to another overloaded function in the Renderer, called "render".
- [BREAKING] SceneObjects passed to the new Renderer.render function are no longer enclosed in a shared_ptr but are plain SceneObjects, passed by reference.
- [BREAKING] SceneObject.collidesWithSceneObject no longer takes a pointer, but a SceneObject, by reference, as parameter.
- [BREAKING] SceneObject.collidesWithSceneObject and SceneObject.collidesWithPoint have been renamed to two overloaded functions, called "collidesWith".
- Corrections to the documentation and introduction of automatic documentation generation, using [codedocs](https://codedocs.xyz/dimi309/small3d/annotated.html)
- [BREAKING] Renamed BoundingBoxes class to BoundingBoxSet
- [BREAKING] Renamed BoundingBoxes (now BoungingBoxSet) functions boxesAreWithin and pointIsWithin to collidesWith (overloaded).
- [BREAKING] Replaced 3 variables which represented a point's coordinates in SceneObject.collidesWith and BoundingBoxSet.collidesWith with a single glm::vec3 variable.
- [BREAKING] The SDL colour parameter in the Renderer.render has been replaced by a glm::uvec4
- [BREAKING] The Renderer.render method for text has had its four indivitual parameters, indicating the coordinates of the top left and the bottom right corner of the rectangle in which the text will be displayed, replaced by two 2-dimensional glm vectors.
- [BREAKING] The rotation logic of the camera and the models has been corrected in the source, as well as the shaders. There were many mistakes and erroneous hacks implemented up to now, because the whole logic was made to accommodate the orientation of the sample models that were created during initial development, rather than conform to a default coordinate system that a programmer could easily understand. A rotation adjustment property has also been added to the SceneObject class (and the corresponding BoundingBoxSet for collision detection), allowing for a fixed adjustment of the objects' orientation in the future, if their meshes are not facing a direction that fits in intuitively with the coordinates of the scene.
