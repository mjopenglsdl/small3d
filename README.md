small3d
=======
*A small, no fuss, 3D game engine*

[![biicode block](http://img.shields.io/badge/dimitrikourk%2Fsmall3d-DEV%3A%201-yellow.svg)](http://www.biicode.com/dimitrikourk/dimitrikourk/small3d/master/1) [![Build Status](https://travis-ci.org/dimitrikourk/small3d.svg?branch=master)](https://travis-ci.org/dimitrikourk/small3d)

Quick start guide: http://goo.gl/5TYOv2

For requests for assistance, please open an issue on the project's source code repository: https://github.com/dimitrikourk/small3d/issues

API documentation: http://small3d.org

You can also follow small3d on Twitter: https://twitter.com/small_3D

![Screen capture from the first game that runs on small3d](https://cloud.githubusercontent.com/assets/875167/4695565/ca5fafb2-5808-11e4-8a81-d186db8b335c.png)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood, rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game, which has been under development for more than a year, as a learning exercise (introduction: http://goo.gl/itn6x5, blog: http://goo.gl/7hCTPA). I have decided to separate the game from its engine and make the engine available for easy reuse, as a biicode block (http://goo.gl/WKS0Hv). The game is now provided as a sample, in the "samplegame" folder within the block, and it demonstrates how the features of the engine can be used.

I will be using this block to make my own games, but one of the reasons I have decided to open source it is so that I can receive feedback and ideas. So please feel free to make suggestions! https://github.com/dimitrikourk/small3d/issues

Compatibility
-------------
**Debian Wheezy - Eclipse**: No problems

**Debian Wheezy - Command Line**: No problems

**Windows - Visual Studio**: No problems. Note that, by default, bii will compile projects in Windows using MinGW's compiler. In order to use Visual Studio, issue one of the following commands from the directory of your project, depending on which version you have installed:

bii cpp:configure -G"Visual Studio 10 2010"

bii cpp:configure -G"Visual Studio 11 2012"

bii cpp:configure -G"Visual Studio 12 2013"

**Windows - MinGW**: No problems, but there is no console text output for the logger and the unit tests, most likely due to the mwindows linker flag.

**Mac**: No problems. Many thanks to hithwen for for providing the first successful compilation on a Mac (https://github.com/dimitrikourk/small3d/commit/26b85780a3ef03c9d5c11f1527803173feaadd1c) and for testing the block.

**Others:** I would expect that the engine and the sample game should work on most other environments with no problems. Before migrating to biicode, I had also spent time developing the engine on Ubuntu and Fedora, so the code is prety mature cross-platform-wise.

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

small3d can play sounds from .ogg files. This is newly developed functionality, so there are still a few glitches, but it will be improved soon. In the meantime, note that the sound facilities of small3d are not tightly coupled at all with the rest of the engine. You can always choose to use an external sound library, if you require more features.
