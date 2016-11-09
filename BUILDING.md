small3d - Building from source code
===================================

Windows
-------
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php) (32-bit development library) or [GLFW](http://www.glfw.org/), depending on which one you prefer to use.
- [GLEW](http://glew.sourceforge.net)
- [GLM](http://glm.g-truc.net/0.9.7/index.html) (source code)
- [PNG](http://libpng.sourceforge.net/) (source code)
- [ZLIB](http://zlib.net/) (source code)
- [Google Test](https://github.com/google/googletest) (source code)
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)
- [FreeType](http://gnuwin32.sourceforge.net/packages/freetype.htm) (binaries archive)

Inside the small3d directory, create a directory called *deps* and, within it, one called *include*, one called *lib* and another one, called *bin*.

#### Set up SDL2 or GLFW
If your are going to use SDL2, unzip its archive, copy the contents of its include directory to *small3d/deps/include*, all the .lib files from its *lib/x86* directory to *small3d/deps/lib* and the .dll files from the same location to *small3d/deps/bin*.

In order to use GLFW, from inside its archive directory, execute:

	mkdir build
	cd build
	cmake ..
	cmake --build .

Then, copy the file *glfw3.lib* from *build/src/Debug* to *small3d/deps/lib* and the *GLFW* directory from inside the archive's *include* directory to *small3d/deps/include*.

#### Build and set up PNG with ZLIB
Unzip the libpng and zlib archives. Place the diectories that will be created in the same parent directory. Then, using Visual Studio, open *libpng/projects/vstudio/vstudio.sln*. Build the whole solution. If zlib cannot be found during the build and you receive an error, make sure the zlib directory name matches exactly the name by which it is referenced in the zlib project within the libpng solution. After the build has been completed, copy all the .lib files from *libpng/projects/vstudio/Debug* to *small3d/deps/lib* and the .dll files from the same directory to *small3d/deps/bin*. Finally, copy all the .h files from *libpng* and *zlib* to *small3d/deps/include*.

#### Build and set up Google Test
Unzip the Google Test archive. From within it, execute:

    cmake -DBUILD_SHARED_LIBS=ON

With Visual Studio, open *gtest.sln*, build it, and then copy all the .lib files from the *Debug* or *Release* directory to *small3d/deps/lib* and the .dll files from the same directory to *small3d/deps/bin*. Finally, copy the *gtest* directory from *include* to *small3d/deps/include*.

#### Build and set up OGG and Vorbis
Unzip the OGG archive. Open the solution libogg_dynamic.sln in *win32/VS2010*, upgrading it to your Visual Studio version if necessary, and build it. Then, copy the .lib files from there to *small3d/deps/lib*, the .dll files to *small3d/deps/bin* and the *ogg* directory from *include* to *deps/include*.

Unzip the Vorbis archive. Open the solution vorbis_dynamic.sln in *win32/VS2010*, upgrading it to your Visual Studio version if necessary. For each of the projects in the solution, add the *include* directory from the OGG archive in *Properties > VC++ Directories > Include Directories* and the *wind32/VS2010/Win32/Debug* directory from the OGG archive in *Properties > VC++ Directories > Library Directories*. Build the entire solution. Then, copy the *vorbis* directory from *include* to *deps/include* and all the .lib files from *wind32/VS2010/Win32/Debug* to *small3d/deps/lib* and the .dll files to *small3d/deps/bin*.

#### Build and set up Portaudio
Unzip the Portaudio archive. Create a directory called *build1* inside the *portaudio* directory. Build the solution using cmake:

    cd build1
    cmake ..
    cmake --build .

Then, from *build1/Debug* copy the *portaudio_x86.lib* file to *small3d/deps/lib*, the *portaudio_x86.dll* file to *small3d/deps/bin* and the .h files from *portaudio/include* to *deps/include*.

#### Set up the rest of the libraries

Unzip the GLEW and GLM archives. For GLEW, copy the .lib files from *lib/Release/Win32* to *small3d/deps/lib*, and the *GL* directory from include to *small3d/deps/include*. Also copy *bin/Release/Win32/glew32.dll* to *small3d/deps/bin*. For GLM, copy the *glm* directory from within the other *glm* directory to *small3d/deps/include* (there are no binaries/libraries). Finally, for FreeType, copy all the contents of the include directory to *small3d/deps/include*, *lib/freetype.lib* to *small3d/deps/lib* and *bin/freetype6.dll* to *small3d/deps/bin*. 

#### Build small3d
Create a directory inside *small3d*, called *build*. Then, if you are using SDL2, build the solution like this:

    cd build
    cmake ..
    cmake --build .

For building with GLFW, things are a little different:

	cd build
	cmake -DWITH_GLFW=1 ..
	cmake --build .

The above mentioned steps are for a 32-bit debug build. With the appropriate modifications and using 64-bit dependencies, a 64-bit build can be produced. The unit tests can be run by executing *small3dTest.exe* in *build/bin*.

MacOS
-----
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:

- [SDL2](https://www.libsdl.org/download-2.0.php) (.framework package) or [GLFW](http://www.glfw.org/), depending on which one you prefer to use.
- [GLEW](http://glew.sourceforge.net)
- [GLM](http://glm.g-truc.net/0.9.7/index.html)
- [Google Test](https://github.com/google/googletest)
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)
- [FreeType](https://www.freetype.org/download.html)
- [bzip2](http://www.bzip.org)

Inside the small3d directory, create a directory called *deps* and, within it, one called *include* and one called *lib*.

#### Set up SDL2 or GLFW

If you are going to use SDL2, place its .framework package in *deps*. Otherwise, in order to use GLFW, from inside its archive directory, execute:

	mkdir build
	cd build
	cmake ..
	cmake --build .

Then, copy the file *libglfw3.a* from *build/src* to *small3d/deps/lib* and the *GLFW* directory from inside the archive's *include* directory to *small3d/deps/include*.

#### Set up OGG, GLEW and Google Test

Build the OGG library, according to the instructions. Also, install it (with *sudo make install*). Build GLEW, Google Test and Vorbis according to the instructions provided in their distributions. Don't run *make install* on them. Copy the contents of their include directories to *small3d/deps/include*. Copy the .a files from the lib directory of GLEW, the .a files from the Google Test build, the .a files from the Vorbis build (from inside *lib/.libs*) to *small3d/deps/lib*.

#### Set up Portaudio

Unzip the Portaudio archive. Create a directory called *build1* inside the *portaudio* directory. Build the solution using cmake:

    cd build1
    cmake ..
    cmake --build .
	
Copy the *libportaudio_static.a* from inside *lib/.libs* of the portaudio archive to *small3d/deps/lib* and the contents of the archive's *include* directory to *small3d/deps/include*.  

#### GLM, Freetype and Bzip2

GLM does not require compiling. Copy the contents of the *glm* directory from inside the distribution (it is in another *glm* directory) to *deps/include*.

Build Freetype. You just need to run *./configure* and *make* inside its archive directory. Copy the *objs/.libs/libfreetype.a* file to *small3d/deps/lib*. Copy the contents of the include directory to *small3d/deps/include*.

Build bzip2. You just need to run make inside its archive directory. Then copy *libbz2.a* to *small3d/deps/lib* and *bzlib.h* to *small3d/deps/include*.

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
            SDL2.framework

Create another directory inside *small3d*, called *build*.

#### For plain-old make

If you are using SDL2:

    cd build
    cmake ..
    cmake --build .

If you are using GLFW:

	cd build
	cmake -DWITH_GLFW=1 ..
	cmake --build .

The unit tests can be run by executing *small3dTest* in *build/bin*.

#### For Xcode

For SDL2:

    cd build
    cmake -G"Xcode" ..
	
For GLFW:

    cd build
    cmake -G"Xcode" -DWITH_GLFW=1 ..

Open the project with Xcode and build it once. Then, select the *small3dTest* scheme in Xcode and run it.

Linux
------
First, install the dependencies. For Debian-based distributions the command is the following:

    sudo apt-get install build-essential cmake libglm-dev libglew-dev libpng12-dev portaudio19-dev libvorbis-dev libfreetype6-dev libbz2-dev
	
Also, if you are planning to use SDL2, you need this:

	sudo apt-get install libsdl2-dev
	
If on the other hand you will be using GLFW:

	sudo apt-get install libglfw3-dev

For Fedora, Red Hat, etc. the dependencies can be acquired as follows:

    sudo yum install libtool glm-devel glew-devel libpng-devel portaudio-devel libvorbis-devel freetype-devel bzip2-devel
	
Then, when building with SDL2, you need:

	sudo yum install SDL2-devel
	
And for GLFW:

	sudo yum install

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

Clone the [small3d repository](https://github.com/coding3d/small3d). Create another directory inside *small3d*, called *build*. Then build the project, either with SDL2, like this:

    cd build
    cmake ..
    cmake --build .
	
Or with GLFW, like this:

	cd build
	cmake -DWITH_GLFW=1 ..
	cmake --build .

The unit tests can be run by executing *small3dTest* in *build/bin*.
