small3d
=======
*A small, no fuss, cross-platform 3D game engine*

![Avoid the Bug 3D sample game](https://cloud.githubusercontent.com/assets/875167/4695565/ca5fafb2-5808-11e4-8a81-d186db8b335c.png)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood, rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game, which has been under development for more than a year, as a [learning exercise](http://goo.gl/itn6x5). In the end, I decided to separate the game from its engine and make the engine available for easy reuse. The game is now provided as a sample, in the "samplegame" folder, and it demonstrates how the features of the engine can be used.

Getting Started
---------------
The best way to get started is to take a look at the source code in *samplegame* and experiment by modifying it before using the engine for your own games. 

You can also compile the API documentation using doxygen. From the small3d repository, execute:

	doxygen doxygenConfig/doxygen

The documentation will be created in a directory called *documentation*, inside the repository. Just open html/index.html. I am using doxygen v1.8.11, but it should compile with other versions too.

In order to build the engine, please see the instructions below, depending on your operating system. 

Precompiled versions of the engine for some systems are also available on [conan.io](https://www.conan.io/source/small3d/1.0.4/coding3d/ci) and more will be added soon. [Here's an example](https://github.com/coding3d/small3d-conan-example) of how to compile the sample game, deploying the engine from there. It is very fast and simple.

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
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)

Inside the small3d directory, create a directory called *deps* and, within it, one called *include* and another one called *lib*.

#### Build and set up PNG with ZLIB
Unzip the libpng and zlib archives. Place the diectories that will be created in the same parent directory. Then, using Visual Studio, open *libpng/projects/vstudio/vstudio.sln*. Build the whole solution. If zlib cannot be found during the build and you receive an error, make sure the zlib directory name matches exactly the name by which it is referenced in the zlib project within the libpng solution. After the build has been completed, copy all the .lib and .dll files from *libpng/projects/vstudio/Debug* to *small3d/deps/lib*. Finally, copy all the .h files from *libpng* and *zlib* to *small3d/deps/include*.

#### Build and set up Google Test
Unzip the Google Test archive. From within it, execute:

    cmake -DBUILD_SHARED_LIBS=ON

With Visual Studio, open *gtest.sln*, build it, and then copy all the .dll and .lib files from the *Debug* or *Release* directory to *small3d/deps/lib*. Finally, copy the *gtest* directory from *include* to *small3d/deps/include*.

#### Build and set up OGG and Vorbis
Unzip the OGG archive. Open the solution libogg_dynamic.sln in *win32/VS2010*, upgrading it to your Visual Studio version if necessary, and build it. Then, copy the .dll and .lib files from there to *small3d/deps/lib* and the *ogg* directory from *include* to *deps/include*.

Unzip the Vorbis archive. Open the solution vorbis_dynamic.sln in *win32/VS2010*, upgrading it to your Visual Studio version if necessary. For each of the projects in the solution, add the *include* directory from the OGG archive in *Properties > VC++ Directories > Include Directories* and the *wind32/VS2010/Win32/Debug* directory from the OGG archive in *Properties > VC++ Directories > Library Directories*. Build the entire solution. Then, copy the *vorbis* directory from *include* to *deps/include* and all the .lib and .dll files from *wind32/VS2010/Win32/Debug* to *deps/lib*.

#### Build and set up Portaudio
Unzip the Portaudio archive. Delete the *portaudio/src/hostapi/asio* directory. Also, around line 54 of the CMakeLists.txt file, you will find the following code:

    IF(ASIOSDK_FOUND)
    OPTION(PA_USE_ASIO "Enable support for ASIO" ON)
    ELSE(ASIOSDK_FOUND)
    OPTION(PA_USE_ASIO "Enable support for ASIO" OFF)
    ENDIF(ASIOSDK_FOUND)

In the second line, replace "ON" with "OFF". All of this is to save trouble by building Portaudio without ASIO support.

Create a directory called *build1* inside the *portaudio* directory. Create the solution using cmake:

    cd build1
    cmake ..

Open the created solution, *portaudio.sln* with Visual Studio. Now you need to find where the file *ksguid.lib* is located inside your Windows SDK. The directory will probably look like *C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib*, depending on your SDK version. Note that we need the directory that contains the 32-bit version of the library. Once you know the directory, open the *portaudio* project properties from within the *portaudio.sln* solution in Visual studio and add the directory to *VC++ Directories > Library Directories*. Build the solution. Then, copy the .lib and .dll files from *build1/Debug* to *deps/lib* and the .h files from *portaudio/include* to *deps/include*.

#### Set up the rest of the libraries
Unzip the SDL2, SDL2_ttf, GLEW and GLM archives. For SDL2 and SDL2_ttf, copy the contents of their include directories to *small3d/deps/include* and all the .lib and .dll files from their *lib/x86* directories to *small3d/deps/lib*. For GLEW, copy the contents of *lib/Release/Win32* to *small3d/deps/lib* and the *GL* directory from include to *small3d/deps/include*. Also copy *bin/Release/Win32/glew32.dll* to *small3d/deps/lib*. Finally, for GLM, copy the *glm* directory from within the other *glm* directory to *small3d/deps/include* (there are no binaries/libraries).

#### Build small3d and the sample game
Create a directory inside *small3d*, called *build*. Then build the solution:

    cd build
    cmake ..
    cmake --build .

Execute *avoidthebug3d.exe* in *build/sampleGames/avoidTheBug/src/Debug*, in order to run the sample game. The unit tests can be run by executing *small3dTest.exe* in *build/small3d/src/Debug*.

The above mentioned steps are for a 32-bit debug build. With the appropriate modifications and using 64-bit dependencies, a 64-bit build can be produced.

Building on OSX
---------------
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [GLEW](http://glew.sourceforge.net)
- [GLM](http://glm.g-truc.net/0.9.7/index.html)
- [Google Test](https://github.com/google/googletest)
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)

Compile and install the dependencies:

- Create a directory called *deps* inside the small3d directory.
- For SDL2 and SDL2_ttf, download the binary packages (.framework) and place them in *deps*.
- Build the OGG library, according to the instructions. Also, install it (with *sudo make install*).
- Build GLEW, Google Test and Vorbis according to the instructions provided in their distributions. Don't run *make install* on them.
- Build Portaudio according to the instructions. You may have to perform the following changes to the *configure* file beforehand, depending on the version you are using and the version of your OSX system:
	- Around line 15790, replace CFLAGS="$CFLAGS -I\$(top_srcdir)/src/os/unix **-Werror**" with CFLAGS="$CFLAGS -I\$(top_srcdir)/src/os/unix **-Wall**"
	- Around line 15821, there are some condition statements, checking the version of your operating system. By copy pasting one of them, add a condition for your version, before the final *else* statement, if it is newer than the ones mentioned there, for example:

	  			elif xcodebuild -version -sdk macosx10.11 Path >/dev/null 2>&1 ; then
	       			mac_version_min="-mmacosx-version-min=10.4"
	       	 		mac_sysroot="-isysroot `xcodebuild -version -sdk macosx10.11 Path`"
- Create a directory called *include* inside *deps* and copy the contents of the include directories of GLEW, Google Test, Vorbis and Portaudio there.
- Create a directory called *lib* inside *deps* and copy the .a files from the lib directory of GLEW, the .a files from the Google Test build, the .a files from the Vorbis build (from inside *lib/.libs*) and the .a file from the Portaudio build (from inside *lib/.libs*) there.  
- GLM does not require compiling. Copy the contents of the *glm* directory from inside the distribution (it is another *glm* directory) to *deps/include*.

In the end, the *deps* directory structure should look like this:

    small3d
        deps
            include
              GL
              glm
              gtest
			  vorbis
			  (and various files starting with *pa_* for Portaudio)
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
    cmake --build .

Then execute *avoidthebug3d* in *build/sampleGames/avoidTheBug/src*, in order to run the sample game. The unit tests can be run by executing *small3dTest* in *build/small3d/src*.

#### For Xcode

    cd build
    cmake -G"Xcode" ..

Open the project with Xcode and build it once. Then, select the *avoidthebug3d* or *small3dTest* scheme in Xcode and run it.

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
    cmake --build .

Then execute *avoidthebug3d* in *build/sampleGames/avoidTheBug/src*, in order to run the sample game. The unit tests can be run by executing *small3dTest* in *build/small3d/src*.

3D models and textures
----------------------

The engine can only read 3D models from Wavefront .obj files. There are many ways to create such a file, but I am exporting them from Blender.

When exporting the models to Wavefront .obj files, make sure you set the options "Include Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing,
the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program. The PNG file can have no transparency information stored (in my case, in order to achieve this, I load it in Gimp, select Image > Flatten Image and then re-export it as a PNG file from there).

The engine also supports manually created bounding boxes for collision detection. In order to create these in Blender for example, just place them in the preferred position over the model and export them to Wavefront separately from the model, only with the options "Apply Modifiers", "Include Edges", "Objects as OBJ Objects" and "Keep Vertex Order". On the contrary to what is the case when exporting the model itself, more than one bounding box objects can be exported to the same Wavefront file.

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
