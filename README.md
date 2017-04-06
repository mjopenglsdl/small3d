small3d
=======

![beaver](https://cloud.githubusercontent.com/assets/875167/20235630/4f653bc4-a897-11e6-97cc-d6d009fe527c.png)

Introduction
------------

![Demo 1](https://cloud.githubusercontent.com/assets/875167/18656425/4781b3d0-7ef1-11e6-83de-e412d5840fec.gif)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. I developed it while learning how to program games and I am still using it for my projects and experiments. In order to learn how to use it, have a look at the example game, [Avoid the Bug 3D](https://github.com/dimi309/AvoidTheBug3D).

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

Building in Windows
-------------------
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:
- [GLFW](http://www.glfw.org/) (source code)
- [GLEW](http://glew.sourceforge.net) (binaries for Windows, 32 and 64 bits are contained in the archive. Don't be fooled by its name)
- [GLM](https://github.com/g-truc/glm) (source code)
- [PNG](http://libpng.sourceforge.net/) (source code)
- [ZLIB](http://zlib.net/) (source code)
- [Google Test](https://github.com/google/googletest) (source code)
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)
- [FreeType](http://gnuwin32.sourceforge.net/packages/freetype.htm) (binaries archive)

Inside the small3d directory, create a directory called *deps* and, within it, one called *include*, one called *lib* and another one, called *bin*.

#### Set up GLFW

In order to use GLFW, from inside its archive directory, execute:

	mkdir build
	cd build
	cmake ..
	cmake --build .

Then, copy the file *glfw3.lib* from *build/src/Debug* to *small3d/deps/lib*, the file  and the *GLFW* directory from inside the archive's *include* directory to *small3d/deps/include*.

#### Set up GLEW and GLM
From the binary archive of GLEW, copy the *include/GL* directory to *small3d/deps/include*. Copy the *glew32.lib* file from *lib/Release/Win32* to *small3d/deps/lib* and the *glew32.dll* file from *bin/Release/Win32* to *small3d/deps/bin*.

GLM does not require compiling. Copy the contents of the *glm* directory from inside the distribution (it is in another *glm* directory) to *small3d/deps/include*.

#### Build and set up PNG with ZLIB
Unzip the libpng and zlib archives. Place the diectories that will be created in the same parent directory. Then, using Visual Studio, open *libpng/projects/vstudio/vstudio.sln*. Build the whole solution. If zlib cannot be found during the build and you receive an error, make sure the zlib directory name matches exactly the name by which it is referenced in the zlib project within the libpng solution. After the build has been completed, copy all the .lib files from *libpng/projects/vstudio/Debug* to *small3d/deps/lib* and the .dll files from the same directory to *small3d/deps/bin*. Finally, copy all the .h files from *libpng* and *zlib* to *small3d/deps/include*.

#### Build and set up Google Test
Unzip the Google Test archive. From within it, execute:

    cmake -DBUILD_SHARED_LIBS=ON
	cmake --build .

Copy all the .lib files from the *googlemock/gtest/Debug* directory to *small3d/deps/lib* and the .dll files from the same directory to *small3d/deps/bin*. Finally, copy the *gtest* directory from *googletest/include* to *small3d/deps/include*.

#### Build and set up OGG and Vorbis
Unzip the OGG archive. Open the solution libogg_dynamic.sln in *win32/VS2010*, upgrading it to your Visual Studio version if necessary, and build it. Then, copy the libogg.lib file from *win32/VS2010/Win32/Debug* to *small3d/deps/lib*, the libogg.dll file from the same *Debug* directory to *small3d/deps/bin* and the *ogg* directory from *include* to *deps/include*.

Unzip the Vorbis archive. Open the solution vorbis_dynamic.sln in *win32/VS2010*, upgrading it to your Visual Studio version if necessary. For each of the projects in the solution, add the *include* directory from the OGG archive in *Properties > VC++ Directories > Include Directories* and the *wind32/VS2010/Win32/Debug* directory from the OGG archive in *Properties > VC++ Directories > Library Directories*. Build the entire solution. Then, copy the *vorbis* directory from *include* to *deps/include* and all the .lib files from *wind32/VS2010/Win32/Debug* to *small3d/deps/lib* and the .dll files to *small3d/deps/bin*.

#### Build and set up Portaudio
Unzip the Portaudio archive. Create a directory called *build1* inside the *portaudio* directory. Build the solution using cmake:

    cd build1
    cmake ..
    cmake --build .

Then, from *build1/Debug* copy the *portaudio_x86.lib* file to *small3d/deps/lib*, the *portaudio_x86.dll* file to *small3d/deps/bin* and the .h files from *portaudio/include* to *deps/include*.

#### Freetype

Copy all the contents of the include directory to *small3d/deps/include*, *lib/freetype.lib* to *small3d/deps/lib* and *bin/freetype6.dll* to *small3d/deps/bin*. 

#### Build small3d
Create a directory inside *small3d*, called *build*. Then, build the solution like this:

    cd build
    cmake ..
    cmake --build .

The above mentioned steps are for a 32-bit debug build. With the appropriate modifications and using 64-bit dependencies, a 64-bit build can be produced. The unit tests can be run by executing *small3dTest.exe* in *build/bin*. For building your own project, you need the files from the *build/include* directory, the libraries from the *build/lib* directory and the dlls from the *build/bin* directory. If you are using cmake, the modules in *small3d/cmake* can be useful.

Building in MacOS / OSX
-----------------------
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:

- [GLFW](http://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net)
- [GLM](https://github.com/g-truc/glm)
- [PNG](http://libpng.sourceforge.net/)
- [Google Test](https://github.com/google/googletest)
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)
- [FreeType](https://www.freetype.org/download.html)
- [bzip2](http://www.bzip.org)

Inside the small3d directory, create a directory called *deps* and, within it, one called *include* and one called *lib*.

#### Set up GLFW

Build GLFW. From inside its archive directory, execute:

	mkdir build
	cd build
	cmake ..
	cmake --build .

Then, copy the file *libglfw3.a* from *build/src* to *small3d/deps/lib* and the *GLFW* directory from inside the archive's *include* directory to *small3d/deps/include*.

#### Set up OGG and VORBIS

Build the OGG library. First you need to edit its *configure* file. Replace the two occurrences of the string:

`-install_name \$rpath/\$soname`

with:

`-install_name \$soname`

Then execute:

    ./configure
    make

Copy the *include/ogg* directory from the archive to *small3d/deps/include* and the *libogg.a* file from *src/.libs* to *small3d/deps/lib*.

Then build the VORBIS library. The procedure is similar to that for OGG, but there are some differences. First, remove the *rpath* strings, as described above. Then, assuming that your small3d directory is in *Users/user/code* for example, execute:

    export LIBS=-L/Users/user/code/small3d/deps/lib
    export CFLAGS=-I/Users/user/code/small3d/deps/include

And then:
    
     ./configure --with-ogg=/Users/user/code/small3d/deps
     make

Copy the *include/vorbis* directory from the archive to *small3d/deps/include* and all the *.a* files from *lib/.libs* to *small3d/deps/lib*.

#### Set up GLEW

Build GLEW. You just need to execute:

    make

from inside its archive directory. Then copy the .a files from the *lib* directory to *small3d/deps/lib* and the *include/GL* directory to *small3d/deps/include*.

#### Set up Google Test

Here's a quick way to build Google Test. From inside its archive directory, execuke:
    
    mkdir build
    cd build
    cmake ..
    cmake --build .

Then, copy the *googletest/include/gtest* directory to *small3d/deps/include* and the *.a* files from *build/googlemock/gtest* to *small3d/deps/lib*.

#### Set up Portaudio

Unzip the Portaudio archive. Create a directory called *build1* inside the *portaudio* directory. Build the solution using cmake:

    cd build1
    cmake ..
    cmake --build .
	
Copy the *libportaudio_static.a* from *build1* to *small3d/deps/lib* and the contents of the portaudio archive's *include* directory to *small3d/deps/include*.  

#### GLM, Freetype, Bzip2 and PNG

GLM does not require compiling. Copy the contents of the *glm* directory from inside the distribution (it is in another *glm* directory) to *deps/include*.

Build Freetype. You just need to run *./configure* and *make* inside its archive directory. Copy the *objs/.libs/libfreetype.a* file to *small3d/deps/lib*. Copy the contents of the include directory to *small3d/deps/include*.

Build bzip2. You just need to run make inside its archive directory. Then copy *libbz2.a* to *small3d/deps/lib* and *bzlib.h* to *small3d/deps/include*.

Build PNG. You just need to run *./configure* and *make* inside its archive directory. Copy the *libpng16.a* file from *.libs* to *small3d/deps/lib*. Copy the contents of the include directory to *small3d/deps/include*.

In the end, the *deps* directory structure should look like this:

    small3d
        deps
            include
              GL
              glm
              gtest
			  vorbis
			  freetype
			  bzlib.h
			  ft2build.h
			  (and various files starting with *pa_* for Portaudio)
            lib
			  libbz2.a
			  libfreetype.a
              libglew.a
              libgtest_main.a
              libgtest.a
			  libportaudio_static.a
			  libglfw3.a

Create another directory inside *small3d*, called *build*.

#### Build small3d

Execute:

	cd build
	cmake ..
	cmake --build .

The unit tests can be run by executing *small3dTest* in *build/bin*. For building your own project, you need the files in the *build/include* directory and the libraries from the *build/lib* directory. If you are using cmake, the modules in *small3d/cmake* can be useful.

Building in Linux
-----------------
First, install the dependencies. For Debian-based distributions the command is the following:

    sudo apt-get install build-essential cmake libglm-dev libglew-dev libpng12-dev portaudio19-dev libvorbis-dev libfreetype6-dev libbz2-dev libglfw3-dev
	
For Fedora, Red Hat, etc. the dependencies can be acquired as follows:

    sudo yum install libtool glm-devel glew-devel libpng-devel portaudio-devel libvorbis-devel freetype-devel bzip2-devel glfw-devel
	
Google Test is also a dependency. For Fedora, things are simple:

    sudo yum install gtest-devel

The package available for Debian (libgtest-dev) provides no binary, so it will not work. The framework needs to be installed manually. If libgtest-dev is already installed, uninstall it:

    sudo apt-get uninstall libgtest-dev

Then, run the following:

    wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz
    tar xvf release-1.7.0.tar.gz
    cd googletest-release-1.7.0/
    cmake -DBUILD_SHARED_LIBS=ON
    sudo cp -a include/gtest /usr/include
    sudo cp -a libgtest_main.so libgtest.so /usr/lib/

Clone the [small3d repository](https://github.com/coding3d/small3d). Create another directory inside *small3d*, called *build*. Then build the project, like this:

    cd build
    cmake ..
    cmake --build .
	
The unit tests can be run by executing *small3dTest* in *build/bin*. For building your own project, you need the files from the *build/include* directory and the libraries from the *build/lib* directory. If you are using cmake, the modules in *small3d/cmake* can be useful.

![Demo 2](https://cloud.githubusercontent.com/assets/875167/18656844/0dc828a0-7ef5-11e6-884b-706369d682f6.gif)

Note on 3D models and textures
------------------------------

When exporting Blender models to Wavefront .obj files, we need to make sure we set the options "Write Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing, the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program.

Collision Detection
-------------------

The engine supports collision detection via manually created bounding boxes. In order to create these in Blender for example, just place them in the preferred position over the model. Ideally, they should be aligned with the axes but that is not mandatory. It will just increase the detection accuracy.

![boundingboxes](https://cloud.githubusercontent.com/assets/875167/19620357/2e03f446-987c-11e6-8517-dfed5ebd885e.png)

Export the bounding boxes to a Wavefront file separately from the model. You can do this if you "save as" a new file after placing the boxes and deleting the original model. During export, only set the options "Apply Modifiers", "Include Edges", "Objects as OBJ Objects" and "Keep Vertex Order". On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.

Sound
-----

small3d can play sounds from .ogg files on all supported platforms. On Linux, you might hear some noise and receive the following error:

**ALSA lib pcm.c:7843:(snd_pcm_recover) underrun occurred**

One way to solve this is to edit the file */etc/pulse/default.pa* (with sudo), disabling *module-udev-detect* and *module-detect*, by commenting out the following lines (inserting a \# in front of each):

	### Automatically load driver modules depending on the hardware available
	#.ifexists module-udev-detect.so
	#load-module module-udev-detect
	#.else
	### Use the static hardware detection module (for systems that lack udev support)
	#load-module module-detect
	#.endif

Then, *module-alsa-sink* and *module-alsa-source* need to be enabled, by uncommenting all lines that look like the following (by removing the \# from in front of each). There could be two or more:

	load-module module-alsa-sink
	load-module module-alsa-source device=hw:1,0

It is advised to make a backup of *default.pa* before making these modifications. A more detailed description of the procedure can be found in this [article](http://thehumble.ninja/2014/02/06/fixing-alsa-lib-pcmc7843snd_pcm_recover-underrun-occurred-while-keeping-pulseaudio-in-your-system/).
