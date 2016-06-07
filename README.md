small3d
=======
*A small, no fuss, 3D game engine*

![Avoid the Bug 3D sample game](https://cloud.githubusercontent.com/assets/875167/4695565/ca5fafb2-5808-11e4-8a81-d186db8b335c.png)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood, rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game, which has been under development for more than a year, as a [learning exercise](http://goo.gl/itn6x5). In the end, I decided to separate the game from its engine and make the engine available for easy reuse. The game is now provided as a sample, in the "samplegame" folder, and it demonstrates how the features of the engine can be used.

Compatibility
-------------
This engine had initially been published as a [biicode](https://github.com/biicode/) block. Unfortunately the biicode service has been taken offline. So now the code can be compiled independenty, using cmake. When biicode was available, the engine would successfully compile and run on Windows, Debian and OSX. So far I have compiled it successfully on OSX and Debian. You should be able to build it on Windows as well with a bit of effort, since the code had been written accordingly.

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

Note that if you try to build the code on Windows, you will also need to download libpng and zlib. They are provided on OSX by default.

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

If you have any problems with the build, or any questions and need help, don't hesitate to [open an issue](https://github.com/coding3d/small3d/issues). The API documentation is also available [online](http://coding3d.github.io/small3d).

Building on Debian
------------------
First, install the dependencies:

    sudo apt-get install build-essential cmake libsdl2-dev libsdl2-ttf-dev libglm-dev libglew-dev libpng12-dev

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

For the time being, the engine can only read 3D models from Wavefront .obj files. There are many ways to create such a file, but I am exporting them from Blender.

When exporting the models to Wavefront .obj files, make sure you set the options "Include Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing,
the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program. The PNG file can have no transparency information stored (in my case, in order to achieve this, I load it in Gimp, select Image > Flatten Image and then re-export it as a PNG file from there).

The engine also supports manually created bounding boxes for collision detection. In order to create these in Blender for example, just place them in the preferred position over the model and export them to Wavefront separately from the model, only with the options "Apply Modifiers", "Include Edges", "Objects as OBJ Objects" and "Keep Vertex Order". On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.

Sound
-----

small3d's sound capabilities have beed removed, but if you look at older commits, you will find the code I had written for providing sound, using portaudio.
