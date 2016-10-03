Chase the Goat 3D
=================

![Demo 2](https://cloud.githubusercontent.com/assets/875167/18656844/0dc828a0-7ef5-11e6-884b-706369d682f6.gif)

Sample game, linking to the engine on conan.io. Accelerate using the spacebar and navigate using the arrow keys.

Build as follows:

	cd ChaseTheGoat3D
	mkdir build
	cd build
	conan install .. --build missing
	cmake ..
	cmake --build .

On Microsoft Windows, better do it like this:

	cd ChaseTheGoat3D
	mkdir build
	cd build
	conan install .. --build missing
	cmake -G "Visual Studio 14 2015 Win64" ..
	cmake --build . --config Release

And then just execute the **chasethegoat3d** executable from the **build/bin** directory.

Happy coding!
