small3d - Building from source code
===================================

Windows
-------
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php) (32-bit development library)
- [GLEW](http://glew.sourceforge.net)
- [GLM](http://glm.g-truc.net/0.9.7/index.html) (source code)
- [PNG](http://libpng.sourceforge.net/) (source code)
- [ZLIB](http://zlib.net/) (source code)
- [Google Test](https://github.com/google/googletest) (source code)
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)
- [FreeType](http://gnuwin32.sourceforge.net/packages/freetype.htm) (binaries archive)

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
Unzip the SDL2, GLEW and GLM archives. For SDL2, copy the contents of its include directory to *small3d/deps/include* and all the .lib and .dll files from its *lib/x86* directory to *small3d/deps/lib*. For GLEW, copy the contents of *lib/Release/Win32* to *small3d/deps/lib* and the *GL* directory from include to *small3d/deps/include*. Also copy *bin/Release/Win32/glew32.dll* to *small3d/deps/lib*. For GLM, copy the *glm* directory from within the other *glm* directory to *small3d/deps/include* (there are no binaries/libraries). Finally, for FreeType, copy all the contents of the include directory to *small3d/deps/include* and *lib/freetype.lib* and *bin/freetype6.dll* to *small3d/deps/lib*. 

#### Build small3d
Create a directory inside *small3d*, called *build*. Then build the solution:

    cd build
    cmake ..
    cmake --build .

The unit tests can be run by executing *small3dTest.exe* in *build/small3d/src/Debug*.

The above mentioned steps are for a 32-bit debug build. With the appropriate modifications and using 64-bit dependencies, a 64-bit build can be produced.

MacOS
-----
Clone the [small3d repository](https://github.com/coding3d/small3d). Then, download and install cmake. And then, download the following dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [GLEW](http://glew.sourceforge.net)
- [GLM](http://glm.g-truc.net/0.9.7/index.html)
- [Google Test](https://github.com/google/googletest)
- [Vorbis and OGG](https://www.xiph.org/downloads/)
- [Portaudio](http://www.portaudio.com/download.html)
- [FreeType](https://www.freetype.org/download.html)
- [bzip2](http://www.bzip.org)

Compile and install the dependencies:

- Create a directory called *deps* inside the small3d directory.
- For SDL2, download the binary package (.framework) and place it in *deps*.
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
- Build Freetype. You just need to run *./configure* and *make* inside its archive directory. Copy the *objs/.libs/libfreetype.a* file to *small3d/deps/lib*. Copy the contents of the include directory to *small3d/deps/include*.
- Build bzip2. You just need to run make inside its archive directory. Then copy *libbz2.a* to *small3d/deps/lib* and *bzlib.h* to *small3d/deps/include*.

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
            SDL2.framework

Create another directory inside *small3d*, called *build*.

#### For plain-old make

    cd build
    cmake ..
    cmake --build .

The unit tests can be run by executing *small3dTest* in *build/small3d/src*.

#### For Xcode

    cd build
    cmake -G"Xcode" ..

Open the project with Xcode and build it once. Then, select the *small3dTest* scheme in Xcode and run it.

Linux
------
First, install the dependencies. For Debian-based distributions the command is the following:

    sudo apt-get install build-essential cmake libsdl2-dev libglm-dev libglew-dev libpng12-dev portaudio19-dev libvorbis-dev libfreetype6-dev libbz2-dev

For Fedora, Red Hat, etc. it is this one:

    sudo yum install libtool SDL2-devel glm-devel glew-devel libpng-devel portaudio-devel libvorbis-devel freetype-devel bzip2-devel

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

Clone the [small3d repository](https://github.com/coding3d/small3d). Create another directory inside *small3d*, called *build*. Then build the project:

    cd build
    cmake ..
    cmake --build .

The unit tests can be run by executing *small3dTest* in *build/small3d/src*.
