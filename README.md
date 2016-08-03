small3d
=======
*A small, no fuss, cross-platform 3D game engine*

- [Documentation](http://coding3d.github.io/small3d)
- [Source Code](https://github.com/coding3d/small3d)

This is a development version. The latest stable release is [1.0.3](https://github.com/coding3d/small3d/releases/tag/1.0.3)

![Avoid the Bug 3D sample game](https://cloud.githubusercontent.com/assets/875167/4695565/ca5fafb2-5808-11e4-8a81-d186db8b335c.png)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood, rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game, which has been under development for more than a year, as a [learning exercise](http://goo.gl/itn6x5). In the end, I decided to separate the game from its engine and make the engine available for easy reuse. The game is now provided as a sample, in the "samplegame" folder, and it demonstrates how the features of the engine can be used.

Compatibility
-------------
The engine has been successfully compiled and tested on Windows, OSX and Linux (Debian).

If you have any problems with the builds, or any questions and need help, don't hesitate to [open an issue](https://github.com/coding3d/small3d/issues).

Building on Windows
-------------------
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php) (32-bit development library)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (32-bit development library)
- [GLEW](http://glew.sourceforge.net)
- [GLM](http://glm.g-truc.net/0.9.7/index.html) (source code)
- [PNG](http://libpng.sourceforge.net/) (source code)
- [ZLIB](http://zlib.net/) (source code)
- [Google Test](https://github.com/google/googletest) (source code)

Inside the small3d directory, create a directory called *deps* and, within it, one called *include* and another one called *lib*.

#### Build and set up PNG with ZLIB
Unzip the libpng and zlib archives. Place the diectories that will be created in the same parent directory. Then, using Visual Studio, open *libpng/projects/vstudio/vstudio.sln*. Build the whole solution. If zlib cannot be found during the build and you receive an error, make sure the zlib directory name matches exactly the name by which it is referenced in the zlib project within the libpng solution. After the build has been completed, copy all the .lib and .dll files from *libpng/projects/vstudio/Debug* to *small3d/deps/lib*. Finally, copy all the .h files from *libpng* and *zlib* to *small3d/deps/include*.

#### Build and set up Google Test
Unzip the Google Test archive. From within it, execute:

    cmake -DBUILD_SHARED_LIBS=ON

With Visual Studio, open *gtest.sln*, build it, and then copy all the .dll and .lib files from the *Debug* or *Release* directory to *small3d/deps/lib*. Finally, copy the *gtest* directory from *include* to *small3d/deps/include*.

#### Set up the rest of the libraries
Unzip the SDL2, SDL2_ttf, GLEW and GLM archives. For SDL2 and SDL2_ttf, copy the contents of their include directories to *small3d/deps/include* and all the .lib and .dll files from their *lib/x86* directories to *small3d/deps/lib*. For GLEW, copy the contents of *lib/Release/Win32* to *small3d/deps/lib* and the *GL* directory from include to *small3d/deps/include*. Also copy *bin/Release/Win32/glew32.dll* to *small3d/deps/lib*. Finally, for GLM, copy the *glm* directory from within the other *glm* directory to *small3d/deps/include* (there are no binaries/libraries).

#### Build small3d and the sample game
Create a directory inside *small3d*, called *build*. Then create the solution:

    cd build
    cmake ..

Open *small3d/build/small3d.sln* with Visual Studio. Build the solution. Then, copy all the .dll files from *small3d/deps/lib* to *small3d/build/Debug*. Aslo copy the resources directoy from *small3d/build* to *small3d/build/debug* and the *samplegame/resources* directory from *small3d/build* to *small3d/build/Debug*, maintaining the same structure (don't merge it with the other resources directory).

From here on you can execute the sample game (*avoidthebug3d.exe*) or the unit tests (*small3dTest.exe*), either by double-clicking on them or via the command line, or debug them with Visual Studio.

The above mentioned steps are for a 32-bit debug build. With the appropriate modifications and using 64-bit dependencies, a 64-bit build can be produced.

Building on OSX
---------------
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [GLEW](http://glew.sourceforge.net)
- [GLM](http://glm.g-truc.net/0.9.7/index.html)
- [Google Test](https://github.com/google/googletest)

Compile and install the dependencies:
- Create a directory called *deps* inside the small3d directory.
- For SDL2 and SDL2_ttf, download the binary packages (.framework) and place them in *deps*.
- Build GLEW and Google Test according to the instructions provided in their distributions. Don't run *make install* on them.
- Create a directory called *include* inside *deps* and copy the contents of the include directories of GLEW and Google Test there.
- Create a directory called *lib* inside *deps* and copy the contents of the lib directories of GLEW and Google Test there, skipping the GLEW .dylib files, since they are not needed.  
- GLM does not require compiling. Copy the contents of the include directory to *deps/include*.

In the end, the *deps* directory structure should look like this:

    small3d
        deps
            include
              GL
              glm
              gtest
            lib
              libglew.a
              libgtest_main.a
              libgtest.a
            SDL2_ttf.framework
            SDL2.framework

Create another directory inside *small3d*, called *build*.

#### For plain-old make

    cd build
    cmake ..
    make

And then just execute *avoidthebug3d*, in order to run the sample game, or *small3dTest* for the unit tests.

#### For Xcode

    cd build
    cmake -G"Xcode" ..

Open the project with Xcode and build it once. Then copy the *resources* and *samplegame/resources* directories to the *Debug* directory created by Xcode (maintaining directory structures). Then, select the *avoidthebug3d* or *small3dTest* scheme in Xcode and run it.

Building on Debian
------------------
First, install the dependencies:

    sudo apt-get install build-essential cmake libsdl2-dev libsdl2-ttf-dev libglm-dev libglew-dev libpng12-dev portaudio19-dev libvorbis-dev

Google Test is also a dependency, but the package available for Debian (libgtest-dev) provides no binary, so it will not work. The framework needs to be installed manually. If libgtest-dev is already installed, uninstall it:

    sudo apt-get uninstall libgtest-dev

Then, run the following:

    wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz
    tar xvf release-1.7.0.tar.gz
    cd googletest-release-1.7.0/
    cmake -DBUILD_SHARED_LIBS=ON
    sudo cp -a include/gtest /usr/include
    sudo cp -a libgtest_main.so libgtest.so /usr/lib/

Clone the [small3d repository](https://github.com/coding3d/small3d). Create another directory inside *small3d*, called *build*. Then build the project:

    cd build
    cmake ..
    make

And then just execute *avoidthebug3d*, in order to run the sample game, or *small3dTest* for the unit tests.

3D models and textures
----------------------

The engine can only read 3D models from Wavefront .obj files. There are many ways to create such a file, but I am exporting them from Blender.

When exporting the models to Wavefront .obj files, make sure you set the options "Include Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing,
the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program. The PNG file can have no transparency information stored (in my case, in order to achieve this, I load it in Gimp, select Image > Flatten Image and then re-export it as a PNG file from there).

The engine also supports manually created bounding boxes for collision detection. In order to create these in Blender for example, just place them in the preferred position over the model and export them to Wavefront separately from the model, only with the options "Apply Modifiers", "Include Edges", "Objects as OBJ Objects" and "Keep Vertex Order". On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.

Sound
-----

small3d's sound capabilities have beed removed, but if you look at older commits, you will find the code I had written for providing sound, using portaudio.
