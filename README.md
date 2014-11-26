small3d
=======
*A small, no fuss, 3D game engine*

[![biicode block](http://img.shields.io/badge/dimitrikourk%2Fsmall3d-DEV%3A%204-yellow.svg)](http://www.biicode.com/dimitrikourk/dimitrikourk/small3d/master/4) [![Build Status](https://travis-ci.org/dimitrikourk/small3d.svg?branch=master)](https://travis-ci.org/dimitrikourk/small3d)

Quick start guide: http://goo.gl/5TYOv2

For requests for assistance, please open an issue on the project's source code repository: https://github.com/dimitrikourk/small3d/issues

API documentation: http://small3d.org

You can also follow small3d on Twitter: https://twitter.com/small_3D

![Screen capture from the first game that runs on small3d](https://cloud.githubusercontent.com/assets/875167/4695565/ca5fafb2-5808-11e4-8a81-d186db8b335c.png)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood, rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game, which has been under development for more than a year, as a learning exercise (introduction: http://goo.gl/itn6x5, blog: http://goo.gl/7hCTPA). I have decided to separate the game from its engine and make the engine available for easy reuse, as a biicode block (http://goo.gl/WKS0Hv). The game is now provided as a sample, in the "samplegame" folder within the block, and it demonstrates how the features of the engine can be used.

The previous version of small3d (3) is stable, but note that it is only a proof-of-technology. You can definitely make interesting things with it, but it is not complete. A lot of values are hardcoded, like the dimensions of the 3D scene or the position of the camera. It also needs a few more features, like better control of text rendering and sound. This version (4) of the block will be the first official release, with all of these matters addressed, a comprehensive, easy to understand API and an architecture that abides to the "Don`t make me use your design" principle (http://blog.biicode.com/software-design-proposal/). At present, it is under heavy development and will be changing a lot.

In order to use version 4 already, you need to configure your policies to accept my DEV tagged versions: http://docs.biicode.com/biicode/configuration_files/policies.html

Feel free to make suggestions! https://github.com/dimitrikourk/small3d/issues

Compatibility
-------------
**Debian Wheezy - Eclipse**: No problems

**Debian Wheezy - Command Line**: No problems

**Windows - Visual Studio**: No problems, but make sure you use biicode v7 of google/gtest (check bii/requirements.bii). There are some conflicts when v8 is used. I am working on them. Note that, by default, bii will compile projects in Windows using MinGW's compiler. In order to use Visual Studio, issue one of the following commands from the directory of your project, depending on which version you have installed:

bii cpp:configure -G"Visual Studio 10 2010"

bii cpp:configure -G"Visual Studio 11 2012"

bii cpp:configure -G"Visual Studio 12 2013"

**Windows - MinGW**: The engine and sample game will compile and work under MinGW but support for that environment is a little flaky (see https://github.com/dimitrikourk/small3d/blob/master/aboutMinGW.txt).
Also, with MinGW, the build time is quite long, so I would strongly recommend using the Visual Studio compiler. You can get Visual Studio Express for free:

http://www.visualstudio.com/downloads/download-visual-studio-vs#d-express-windows-desktop

**Mac**: No problems. Many thanks to hithwen for for providing the first successful compilation on a Mac (https://github.com/dimitrikourk/small3d/commit/26b85780a3ef03c9d5c11f1527803173feaadd1c) and for testing the block.

**Others:** I would expect that the engine and the sample game should work on most other environments with no problems. Before migrating to biicode, I had also spent time developing the engine on Ubuntu and Fedora, so the code is prety mature cross-platform-wise.

Note about 3D models and textures
---------------------------------

For the time being, the engine can only read 3D models from Wavefront .obj files. There are many ways to create such a file, but I am exporting them from Blender.

When exporting the models to Wavefront .obj files, make sure you set the options "Include Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing,
the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program. The PNG file can have no transparency information stored (in my case, in order to achieve this, I load it in Gimp, select Image > Flatten Image and then re-export it as a PNG file from there).

The engine also supports manually created bounding boxes for collision detection. In order to create these in Blender for example, just place them in the preferred position over the model and export them to Wavefront separately from the model, only with the options "Apply Modifiers", "Include Edges", "Objects as OBJ Objects" and "Keep Vertex Order". On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.
