small3d changelog
=================

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
