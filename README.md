small3d
=======
*A small, no fuss, 3D game engine*

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood, rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game, which has been under development for more than a year, as a [learning exercise](http://goo.gl/itn6x5). In the end, I decided to separate the game from its engine and make the engine available for easy reuse. The game is now provided as a sample, in the "samplegame" folder, and it demonstrates how the features of the engine can be used.

Compatibility
-------------
This engine had initially been published as a [biicode](https://github.com/biicode/) block. Unfortunately the biicode service has been taken offline. So now the code can be compiled independenty, using cmake. When biicode was available, the engine would successfully compile and run on Windows, Debian and OSX, but I have only compiled the independent build on OSX so far. You should be able to build it on other platforms as well, since the code had been written accordingly.

Building
--------
Download and install cmake. Then, download the following dependencies:
- SDL2
- SDL2_ttf
- GLEW
- GLM
- Google Test

For SDL2 and SDL2_ttf, download the binary packages. Then you need to build GLEW and Google Test according to the instructions provided in their distributions. Don't run *make install* on them. We are going to place them in a specific directory. GLM does not require compiling.

Once the above is done, create a directory called *deps* inside the small3d directory. Copy the libraries and compiled packages there. The only exception is the glm header files, which you should place in a directory called *include* (create it inside *deps*). The whole thing should look like this:

    small3d
        deps
            glew
            googletest
            include
              glm
            SDL2_ttf.framework
            SDL2.framework

Create another directory inside *small3d*, called *build*.

#### For plain-old make

    cd build
    cmake ..
    make

And then just execute avoidthebug3d

#### For Xcode

    cd build
    cmake -G"Xcode" ..

Open the project with Xcode and build it once. Then copy the *resources* and *samplegame/resources* directories to a singe *resources* directory inside the *Debug* directory created by Xcode. Then, select the avoidthebug3d scheme in Xcode and run it.

If you have any problems with the build, or any questions and need help, don't hesitate to [open an issue](https://github.com/coding3d/small3d/issues).

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
