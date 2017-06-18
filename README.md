small3d
=======

![beaver](https://cloud.githubusercontent.com/assets/875167/20235630/4f653bc4-a897-11e6-97cc-d6d009fe527c.png)

Introduction
------------

![Demo 1](https://cloud.githubusercontent.com/assets/875167/18656425/4781b3d0-7ef1-11e6-83de-e412d5840fec.gif)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. I developed it while learning how to program games and I am still using it for my projects and experiments. In order to learn how to use it, have a look at the [tutorial](https://github.com/dimi309/small3d-tutorial) and the [API documentation](http://dimi309.github.io/small3d/).

Features
--------

- Runs on Windows, Mac, Linux (I have tested it on Debian and Fedora and somebody has told me that it works on Ubuntu, too).
- It works with GLFW.
- Uses OpenGL 3.3 and defaults to 2.1 if the former is not available. So, it comes with two sets of shaders.
- Uses C++11.
- You can tweak the engine's shaders, as long as you keep the same incoming variables and uniforms.
- Plays sounds from .ogg files.
- Doesn't hide GLFW or OpenGL from you. You can set up your main game loop, inputs, etc, however you want, use its functionality, but also code around it making your own OpenGL calls for example.
- It can read and render Wavefront files, including animations. Personally, I use Blender to create the models and export these files.
- Texture mapping.
- It can render any image in any position (for example to be used as the ground, or the sky).
- Gouraud shading. You can set the light direction and intensity.
- Simple rotations with matrices.
- Simple collision detection with bounding boxes.
- It renders text.
- Very permissive license (3-clause BSD). The libraries it uses have been chosen to have a permissive license also.
- **It can be deployed via a package manager (conan). This is a huge time saver and you can see in the abovementioned [tutorial](https://github.com/dimi309/small3d-tutorial) how to use it.**

Building locally and running the unit tests
-------------------------------------------

Prerequisites:

- A compiler. You can use gcc, Xcode, llvm or Visual Studio, depending on your system. Sadly, MinGW builds are not supported yet.
- [conan](https://github.com/conan-io/conan)
- [CMake](https://cmake.org/)
- [Git](https://git-scm.com/)

Here's how to build and run the project:

	conan remote add bintraydimi309 https://api.bintray.com/conan/dimi309/conan-packages # Only execute this once. Conan will remember it afterwards.
	git clone https://github.com/dimi309/small3d
	cd small3d
	mkdir build
	cd build
	conan install ..
	cmake ..
	cmake --build .
	cd bin
	./small3dTest # Or "small3dTest.exe" if you are on Windows
	
If you are using Visual Studio, depending on its version, you can get some compiler detection and linking errors. Feel free to [ask me](https://github.com/dimi309/volcanique/issues) and I'll be happy to help.

Nonetheless, here's a sure-fire way to make the above mentioned commands work just like that with Visual Studio 2017:

Set the vs150comntools environment variable:
	
	set vs150comntools=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\

In your home directory, make sure that the .conan/conan.conf file contains these lines exactly under settings_defaults:

	[settings_defaults]

	arch=x86
	build_type=Debug
	os=Windows
	compiler=Visual Studio
	compiler.version=15
	compiler.runtime=MDd

Note on 3D models and textures
------------------------------

The Wavefront .obj files used for the engine's models have to have a certain structure. Exporting them from Blender for example,  we need to make sure we set the options "Write Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing, the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program.

Collision Detection
-------------------

The engine supports collision detection via manually created bounding boxes. In order to create these in Blender for example, just place them in the preferred position over the model. Ideally, they should be aligned with the axes but that is not mandatory. It will just increase the detection accuracy.

![boundingboxes](https://cloud.githubusercontent.com/assets/875167/19620357/2e03f446-987c-11e6-8517-dfed5ebd885e.png)

Export the bounding boxes to a Wavefront file separately from the model. You can do this if you "save as" a new file after placing the boxes and deleting the original model. During export, only set the options "Apply Modifiers", "Include Edges", "Objects as OBJ Objects" and "Keep Vertex Order". On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.

![Demo 2](https://cloud.githubusercontent.com/assets/875167/18656844/0dc828a0-7ef5-11e6-884b-706369d682f6.gif)
