small3d
=======
*A small, no fuss, 3D game engine*

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood, rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game, which has been under development for more than a year, as a [learning exercise](http://goo.gl/itn6x5). In the end, I decided to separate the game from its engine and make the engine available for easy reuse, as a biicode block. The game was then provided as a sample, in the "samplegame" folder within the block, and it demonstrated how the features of the engine can be used.

*Unfortunately the biicode service has been taken offline. I am in the process of producing an independent build for small3d. For the moment, the library and sample game work on OSX. I am now cleaning up the code and updating the documentation. I will then provide builds for Windows and Linux.*

Compatibility
-------------

When biicode was available, the engine would successfully compile and run on Windows, Debian and OSX.

License
-------

small3d is licensed under the BSD 3-Clause License (see LICENSE file).

Reuse and packaging
-------------------

Please consider this text (and the whole of this README file for that matter) informative, since I am not a lawyer and I do not accept responsibility for any consequence that may arise from following my indications :)

I would not want there to be any limitations or inconveniences in the use of small3d, so much for free and open source as for commercial and closed source products. This is the reason that I have chosen the BSD 3-Clause License for the engine and I have made sure that all the libraries it is referencing are released under permissive licenses, like BSD, MIT or ZLIB. I have placed the licenses from those libraries in the libsLicenses folder for your convenience during packaging, suffixed with the block versions from which they are being retrieved by the small3d block. In general, there should be no problem in reusing small3d in any manner, provided that you, in SOME cases, reproduce the license text and give credit to the authors of the referenced libraries.

3D models and textures
----------------------

For the time being, the engine can only read 3D models from Wavefront .obj files. There are many ways to create such a file, but I am exporting them from Blender.

When exporting the models to Wavefront .obj files, make sure you set the options "Include Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing,
the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program. The PNG file can have no transparency information stored (in my case, in order to achieve this, I load it in Gimp, select Image > Flatten Image and then re-export it as a PNG file from there).

The engine also supports manually created bounding boxes for collision detection. In order to create these in Blender for example, just place them in the preferred position over the model and export them to Wavefront separately from the model, only with the options "Apply Modifiers", "Include Edges", "Objects as OBJ Objects" and "Keep Vertex Order". On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.

Sound
-----

small3d's sound capabilities have beed disabled for the time being, but they will be reintroduced soon.