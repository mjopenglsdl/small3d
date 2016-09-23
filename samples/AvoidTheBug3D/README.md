Avoid the Bug 3D
=================

Sample game, linking to the engine on conan.io. Move the goat around using the arrow keys, making sure the flying bug does not touch it, for the maximum amount of time.

Build as follows:

	cd AvoidTheBug3D
	conan install --build missing
	mkdir build
	cd build
	cmake ..
	cmake --build .

On Microsoft Windows, better do it like this:

	cd AvoidTheBug3D
	conan install --build missing
	cd build
	cmake -G "Visual Studio 14 2015 Win64" ..
	cmake --build . --config Release

And then just execute the **avoidthebug3d** executable from the **build/bin** directory.

Happy coding!
