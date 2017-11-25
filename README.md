small3d
=======

![beaver](https://cloud.githubusercontent.com/assets/875167/20235630/4f653bc4-a897-11e6-97cc-d6d009fe527c.png) ![Demo 1](https://cloud.githubusercontent.com/assets/875167/18656425/4781b3d0-7ef1-11e6-83de-e412d5840fec.gif)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and using OpenGL with shaders.

- [Tutorial](https://github.com/dimi309/small3d-tutorial): Start here to learn the basics. The repository also includes two sample games that use all of small3d's features.
- [API documentation](http://dimi309.github.io/small3d/): Use this as a reference while developing with the engine.

Features
--------

- Runs on Windows (Visual Studio & MinGW builds), Mac, Linux(regularly tested on Debian, Fedora and Ubuntu).
- It works with GLFW.
- Uses OpenGL 3.3 and defaults to 2.1 if the former is not available.
- Uses C++11.
- You can tweak the engine's shaders, as long as you keep the same incoming variables and uniforms.
- Plays sounds from .ogg files.
- Doesn't hide GLFW or OpenGL from you. You can set up your main game loop, inputs, etc, however you want, use its functionality, but also code around it making your own OpenGL calls for example.
- It can read and render models from Wavefront files, including animations. Personally, I use Blender to create the models.
- Texture mapping.
- It can render any image in any position (for example to be used as the ground, or the sky).
- Gouraud shading. You can set the light direction and intensity.
- Simple rotations with matrices.
- Simple collision detection with bounding boxes.
- It renders text.
- Very permissive license (3-clause BSD). The libraries it uses have been chosen to have a permissive license also.
- It is deployed via a package manager (conan). This is a huge time saver and you can see in the abovementioned [tutorial](https://github.com/dimi309/small3d-tutorial) how to use it.

Building locally
----------------

Apart from deploying the engine for your projects, you might like to explore the source code and run the unit tests, in order to better understand it or make modifications. In that case, you can build it locally on its own. This is how I work while maintaining it and adding features.

Prerequisites:

- A compiler. You can use gcc, Xcode, clang or Visual Studio, depending on your system.
- [conan](https://github.com/conan-io/conan) - If you are using the gcc compiler, please set compiler.libcxx to libstdc++11
- [CMake](https://cmake.org/)
- [Git](https://git-scm.com/)

Add the bincrafters bintray repository. [Bincrafters](https://bincrafters.github.io/) is a group of OSS developers with a shared interest in making binary software packages. You only need to execute this once. Conan will remember it afterwards:

	conan remote add bintraybincrafters https://api.bintray.com/conan/bincrafters/public-conan

Also, add my bintray repository as a remote to your conan configuration:

	conan remote add bintraydimi309 https://api.bintray.com/conan/dimi309/conan-packages
	
Finally, add the following bintray repository (that's where I get the portaudio dependency from):

	conan remote add bintrayjgsogo https://api.bintray.com/conan/jgsogo/conan-packages
	
**TEMPORARILY, YOU HAVE TO DO THE FOLLOWING BEFORE PROCEEDING. THIS IS BECAUSE OF ADAPTATIONS TO THE LATEST VERSION OF CONAN THAT HAVE NOT YET BEEN COMPLETED**

	git clone https://github.com/dimi309/conan-freetype
	cd conan-freetype
	git checkout testing/2.8.1
	conan create bincrafters/stable --build missing
	cd ..

Then, run the following:

	git clone https://github.com/dimi309/small3d
	cd small3d
	mkdir build
	cd build
	conan install ..
	conan build ..
	cd build
	
And then execute `./unittests` on MacOS or Linux, or `unittests.exe` if you are running Windows.

In order to deploy the package locally, so that you can reference it from your own projects, just run the following from the small3d source directory:

	conan create dimi309/stable

If you encounter any problems, feel free to [ask me](https://github.com/dimi309/volcanique/issues) and I'll be happy to help.

If you are using Visual Studio 2017, conan may not be able to detect it. In that case, set the vs150comntools environment variable:
	
	set vs150comntools=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\

In your home directory, make sure that the .conan/profiles/default file contains this:

	[settings]
	arch=x86
	build_type=Debug
	os=Windows
	compiler=Visual Studio
	compiler.version=15
	compiler.runtime=MDd
	
If you are using MinGW, you have to link dynamically to gtest (run conan install with -o gtest:shared=True) and MinGW has to have pthreads installed. A good configuration for a conan profile file in that case would be the following:

	[settings]
	arch=x86
	build_type=Release
	os=Windows
	compiler=gcc
	compiler.version=6.3
	compiler.libcxx=libstdc++11

Note on 3D models and textures
------------------------------

The Wavefront .obj files used for the engine's models have to have a certain structure. Exporting them from Blender for example,  we need to make sure we set the options **"Write Normals"**, **"Triangulate Faces"**, and **"Keep Vertex Order"**. When exporting animations, also set **"Apply modifiers"**. Only one object should be exported to each Wavefront file (the engine cannot read more than one).

If a texture has been created, the option **"Include UVs"** must also be set. The texture should be saved as a PNG file.

Collision Detection
-------------------

The engine supports collision detection via manually created bounding boxes. In order to create these in Blender for example, just place them in the preferred position over the model. Ideally, they should be aligned with the axes but that is not mandatory. It will just increase the detection accuracy.

![boundingboxes](https://cloud.githubusercontent.com/assets/875167/19620357/2e03f446-987c-11e6-8517-dfed5ebd885e.png)

Export the bounding boxes to a Wavefront file separately from the model. You can do this if you "save as" a new file after placing the boxes and deleting the original model. During export, only set the options **"Apply Modifiers"**, **"Include Edges"**, **"Objects as OBJ Objects"** and **"Keep Vertex Order"**. On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.

![Demo 2](https://cloud.githubusercontent.com/assets/875167/18656844/0dc828a0-7ef5-11e6-884b-706369d682f6.gif)
