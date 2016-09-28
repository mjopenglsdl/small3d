Avoid the Bug 3D
=================

![Demo 1](https://cloud.githubusercontent.com/assets/875167/18656425/4781b3d0-7ef1-11e6-83de-e412d5840fec.gif)

Sample game, linking to the engine on conan.io. Move the goat around using the arrow keys, making sure the flying bug does not touch it, for the maximum amount of time.

Build as follows:

	cd AvoidTheBug3D
	mkdir build
	cd build
	conan install .. --build missing
	cmake ..
	cmake --build .

On Microsoft Windows, better do it like this:

	cd AvoidTheBug3D
	mkdir build
	cd build
	conan install .. --build missing
	cmake -G "Visual Studio 14 2015 Win64" ..
	cmake --build . --config Release

And then just execute the **avoidthebug3d** executable from the **build/bin** directory.

Happy coding!
