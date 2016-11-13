small3d
=======

[![Build status](https://ci.appveyor.com/api/projects/status/vl7gmu89v7194o2t?svg=true)](https://ci.appveyor.com/project/coding3d/small3d) [![Build Status](https://travis-ci.org/dimi309/small3d.svg?branch=master)](https://travis-ci.org/dimi309/small3d) [![badge](https://img.shields.io/badge/conan.io-small3d%2F1.1.1-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/small3d/1.1.1/coding3d/stable)


![beaver](https://cloud.githubusercontent.com/assets/875167/20235630/4f653bc4-a897-11e6-97cc-d6d009fe527c.png)

**The API documentation is available at http://dimi309.github.io/small3d/**

Introduction
------------

![Demo 1](https://cloud.githubusercontent.com/assets/875167/18656425/4781b3d0-7ef1-11e6-83de-e412d5840fec.gif)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. I developed it while learning how to program games and I am still using it for my projects and experiments.

A Bit of History
----------------

*You don't need to read this to use the engine. Skip it if you're not interested.*

I'm a hoybbyist and permanent beginner in game development. I had always wanted to make games since I was a kid but, even though I have been working in IT for years, mostly as a developer, my work has nothing to do with games, graphics or anything of the sort.

A couple of years ago I thought that if I want to learn how to do this I might as well start. I'm interested in programming so I did not opt for a ready-made game engine. I get it that this is how most game development is carried out today and that it is a bad business decision to program everything by hand ("by hand" is relative as can be attested by the libraries I am using - we are always "standing on the shoulders of giants"). I probably wouldn't do so if my income depended on it. If I understand it correctly, professionals who do write their own rendering logic or physics algorithms end up specialising in one specific area. Those who actually develop entire games just pick a multi-featured tool and study how to use it rather than how to push vertices to the GPU.

As I've mentioned, I was not looking to start a new career so I thought to proceed the way my 80s heroes would, writing code in their living rooms. So I started making a little game in which a bug is chasing a goat. Some have told me that the bug looks like a crow and the goat looks like a unicorn, which is understandable, since I'm also doing my own 3D modelling with Blender. Once the game was finished, I thought to put the functionality that could be reused in a library and this is how the small3d engine came to be.

One question I got at some point was why I did not follow the advice, "write games not engines". I've found a copy of the [article that says this](http://www.geometrian.com/programming/tutorials/write-games-not-engines/index.php) and I'm not sure that the author meant "just download an engine and get started". What I've done is not so far off from what he proposes, even though I may have been in a bit of a rush. But then again, I think it's good to be building a toolset of reusable items whenever you are working on something, no matter how much you have progressed.


Features
--------

- Runs on Windows, Mac, Linux (I have tested it on Debian and Fedora and somebody has told me that it works on Ubuntu, too).
- It can be built with either SDL or GLFW.
- Uses OpenGL 3.3 and defaults to 2.1 if the former is not available. So, it comes with two sets of shaders.
- Uses C++11.
- You can tweak the engine's shaders, as long as you keep the same incoming variables and uniforms.
- Plays sounds from .ogg files.
- Doesn't hide SDL, GLFW or OpenGL from you. You can set up your main game loop, inputs, etc, however you want, use its functionality, but also code around it making your own OpenGL calls for example.
- It can read and render Wavefront files, including animations.
- Texture mapping.
- It can render any image in any position (for example to be used as the ground, or the sky).
- Gouraud shading. You can set the light direction and intensity.
- Simple rotations with matrices.
- Simple collision detection with bounding boxes.
- It renders text.
- It can be deployed via the [conan.io](https://www.conan.io) package manager. This is a great time saver.
- It can also be compiled independently, using CMake.
- Very permissive license (3-clause BSD). The libraries it uses have been chosen to have a permissive license also.

Getting Started
---------------

Let's get right to it. You can do this on Windows, Linux or MacOS. If you encounter difficulties [let me know](https://github.com/dimi309/small3d/issues). We are going to create a ball that can be moved using the keyboard arrows. Even though small3d is small, it can do a lot more than this. But this exercise will get you started and then you can continue, using the [API documentation](http://dimi309.github.io/small3d/) and having a look at the source code of two games that have already been developed with the engine ([Avoid the Bug 3D](https://github.com/dimi309/AvoidTheBug3D) and [Chase the Goat 3D](https://github.com/dimi309/ChaseTheGoat3D)). The source code for this tutorial, including the model of the ball we will be creating is [available online](https://github.com/dimi309/small3d-tutorial).

I assume that you already have your compiler set up. You also need to install [cmake](https://cmake.org) and [conan](https://www.conan.io) and make sure they can be executed from the command line. I prefer to use the engine by deploying it from conan.io and that's what I'm doing in the tutorial below. It saves me a lot of time. However, if you prefer to compile it yourself without conan, there are [instructions](BUILDING.md) about how to do this. Also, the [Avoid the Bug 3D](https://github.com/dimi309/AvoidTheBug3D) repository has five branches, each being an example of a way the engine can be used (with GLFW or SDL, using conan or building independently, as well as building with [cppan](https://cppan.org/pvt.coding3d.small3d)).

To begin with, let's make a directory for our ball-moving masterpiece from the command line:

	mkdir ball

Also, create a "resources" directory inside the "ball" directory:

	cd ball
	mkdir resources

Let's start from the code-less part. We need a Wavefront file containing a ball. You can use any tool that exports this format to create one, but I am using [Blender](https://www.blender.org), so I'll show you how to do this there. When you start Blender, you see a cube:

![blendercube](https://cloud.githubusercontent.com/assets/875167/19621157/15ee0f9e-988c-11e6-9c8a-b871bd7cdfa9.png)

Press "a" to select the cube. If the cube is selected already, pressing "a" will de-select it. Press it again in that case. Then "x" to delete the cube. You will be asked to confirm the deletion:

![blenderconfirmdeletion](https://cloud.githubusercontent.com/assets/875167/19621164/2c33f778-988c-11e6-8dc0-aec7be490bcc.png)

Just press enter to do so. Then, from the menu at the bottom left of the 3D view, select Add > Mesh > UV Sphere:

![blenderaddsphere](https://cloud.githubusercontent.com/assets/875167/19621171/41a9a346-988c-11e6-9522-02972fdfc57e.png)

This will create, as the name implies, a sphere:

![blendersphere](https://cloud.githubusercontent.com/assets/875167/19621175/561dfc78-988c-11e6-94f0-711369ce364b.png)

With the sphere selected (use the "a" key if it is not), click on the "Smooth" button, under "Shading" on the "Edit" menu on the left of the screen:

![smoothshading](https://cloud.githubusercontent.com/assets/875167/19621180/6ad2ff56-988c-11e6-96bf-36df739e85e7.png)

This is important for the way the sphere will be exported. We now need to create the Wavefront file. From the menu at the top, select File > Export > Wavefront (.obj). We need to set some options on the "Export OBJ" menu on the left. Only select "Write Normals", "Triangulate Faces" and "Keep Vertex Order":

![wavefrontexportoptions](https://cloud.githubusercontent.com/assets/875167/19621183/7da81a76-988c-11e6-9e50-604699e62900.png)

Save the exported file as "ball.obj" in the "resources" directory, created earlier (there is a location and name selector at the top and an "Export OBJ" button to actually save the file).

Now we are ready for the code. Create a file called "main.cpp" in the "ball" directory, with your editor or IDE. For starters let's just make our program use small3d. One class that we will definitely need is Renderer. This one creates a window and, as the name implies, takes care of all the rendering. So here is our main.cpp, with Renderer included:

	#include <small3d/Renderer.hpp>
	
	int main(int argc, char **argv) {
		
		return 0;
	}

Notice that we have not downloaded small3d from anywhere. Let's tell conan to do that for us. Create a file called "conanfile.txt" in the "ball" directory. Inside that file we declare small3d as our dependency:

	[requires]
	small3d/1.1.1@coding3d/stable

We also need to mention that we will be working with cmake:

	[generators]
	cmake

For Windows, we will need the dlls of the libraries we are using (small3d and its dependencies will be automatically downloaded by conan and some of them are not configured to be statically linked) to be copied to our binary output directory. Let's tell conan to take care of that for us:

	[imports]
	bin, *.dll -> ./bin

If you don't use Windows, you can still add that to your conanfile. It will allow your program to compile and run on Windows, should you ever want to do that and, on any other system, it will cause no problem since conan will not crash or anything if it doesn't find any dlls. It just won't copy them.

Finally, we are going to need the small3d shaders. Let's tell conan to also copy those, under [imports]:

	[imports]
	bin, *.dll -> ./bin
	shaders, * -> ./bin/resources/shaders

So the whole conanfile.txt will look like this:

	[requires]
	small3d/1.1.1@coding3d/stable
	
	[generators]
	cmake
	
	[imports]
	bin, *.dll -> ./bin
	shaders, * -> ./bin/resources/shaders
	

Let's see if it works. We are going to be building in a separate directory, in order to keep things clean. From inside the "ball" directory, execute:

	mkdir build
	cd build
	conan install .. --build missing

Conan will download small3d and all libraries that it depends on and place them in a local cache. It will also create its own cmake configuration file (conanbuildinfo.cmake) and, as instructed, copy small3d's shaders to the bin/resources/shaders directory. We are now ready to create our cmake configuration. Back inside the "ball" directory, let's create a CMakeLists.txt file. We will set the minimum required cmake version and declare our project:

	CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)
	PROJECT(demo)

Then we will link our project with conan, by including the conan cmake configuration created in the previous step and then setting up conan with a command contained in it:

	INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	CONAN_BASIC_SETUP()

Since conan does all the hard work of gathering information about our project and environment, let's use that to set up the flags for our build:

	set(CMAKE_C_FLAGS "${CONAN_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CONAN_CXX_FLAGS}")
	set(CMAKE_SHARED_LINKER_FLAGS "${CONAN_SHARED_LINKER_FLAGS}")

We can now declare our executable, also linking it with the conan downloaded libraries:

	ADD_EXECUTABLE(ball main.cpp)
	TARGET_LINK_LIBRARIES(ball PUBLIC "${CONAN_LIBS}")

Each library may require some special link flags. Conan knows about those too, so we'll let it take care of them for us:

	SET_TARGET_PROPERTIES(ball PROPERTIES LINK_FLAGS "${CONAN_EXE_LINKER_FLAGS}")

And, finally, in order for our compiled program to be able to easily access our ball model, which we created earlier, let's have it copied by cmake to the binary output directory:

	FILE(COPY "resources" DESTINATION "${PROJECT_BINARY_DIR}/bin")

So the whole CMakeLists.txt file should look like this:

	CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)
	PROJECT(demo)
	
	INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	CONAN_BASIC_SETUP()
	
	set(CMAKE_C_FLAGS "${CONAN_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CONAN_CXX_FLAGS}")
	set(CMAKE_SHARED_LINKER_FLAGS "${CONAN_SHARED_LINKER_FLAGS}")
	
	ADD_EXECUTABLE(ball main.cpp)
	TARGET_LINK_LIBRARIES(ball PUBLIC "${CONAN_LIBS}")
	SET_TARGET_PROPERTIES(ball PROPERTIES LINK_FLAGS "${CONAN_EXE_LINKER_FLAGS}")
	
	FILE(COPY "resources" DESTINATION "${PROJECT_BINARY_DIR}/bin")
	

Let's see if everything works:

	cd build
	cmake ..
	cmake --build .

On Windows, you need to do this, adding some configuration parameters, depending on your development setup. For example:

	cd build
	cmake -G "Visual Studio 14 2015 Win64" ..
	cmake --build . --config Release

This will compile our program. Inside the build/bin directory, there should be a ball (or ball.exe) executable. At this point though, it doesn't do much. Time to add our ball to the mix. Back in main.cpp, we include small3d's SceneObject class, right under the inclusion of the renderer class (or above it, it doesn't matter):

	#include <small3d/Renderer.hpp>
	#include <small3d/SceneObject.hpp>

We also need to be using the small3d namespace, so this goes under our include statements:

	using namespace small3d;

And finally, we go to the main program, and we create the renderer:

	Renderer renderer("Ball demo");

We create the ball:

	SceneObject ball("ball", "resources/ball.obj");

Let's say it's yellow:

	ball.colour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);

small3d uses vectors a lot as parameters for convenience. In this case, the vector symbolises an rgb colour, together with the alpha channel (last component).

On the other hand, when positioning the ball, the components are in order, x (-left, +right), y(+up, -down), and z(-away from the camera, +towards the camera):

	ball.offset = glm::vec3(0.0f, -1.0f, -8.0f);

So let's start our main loop now. small3d uses SDL and you can use it too! The first thing to do in every iteration, is to check whether we want to exit the program. Let's say that we'll be doing that with the Esc key:

	while(true){
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				break;
			}
	  }

If after that we are still in the loop (so, no Esc key pressed), we will want to move the ball around with the keyboard. We get the key state:

	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

We will have the up arrow move the ball away from the camera. Down will do the opposite. Guess what left and right will do :)

	if (keyState[SDL_SCANCODE_UP] == 1)
		ball.offset.z -= 0.1f;
	else if (keyState[SDL_SCANCODE_DOWN] == 1)
		ball.offset.z += 0.1f;
	else if (keyState[SDL_SCANCODE_LEFT] == 1)
		ball.offset.x -= 0.1f;
	else if (keyState[SDL_SCANCODE_RIGHT] == 1)
		ball.offset.x += 0.1f;

Ok, the ball is positioned. Now we need to actually draw it. We clear the screen first:

	renderer.clearScreen();

Then we render the ball:
	
	renderer.render(ball);

We are using a double-buffered system (we draw on one buffer, while the user is looking at the other one), so we also need to swap the buffers:

	renderer.swapBuffers();

And we close the loop :)

	}

That's it! The whole program should look like this:

	#include <small3d/Renderer.hpp>
	#include <small3d/SceneObject.hpp>

	using namespace small3d;
	
	int main(int argc, char **argv) {
	
		Renderer renderer("Ball demo");
	
		SceneObject ball("ball", "resources/ball.obj");
		ball.colour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		ball.offset = glm::vec3(0.0f, -1.0f, -8.0f);
	
		while(true){
	        SDL_Event event;
	        if (SDL_PollEvent(&event)) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					break;
				}
		  }
	  
		const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	
		if (keyState[SDL_SCANCODE_UP] == 1)
			ball.offset.z -= 0.1f;
		else if (keyState[SDL_SCANCODE_DOWN] == 1)
			ball.offset.z += 0.1f;
		else if (keyState[SDL_SCANCODE_LEFT] == 1)
			ball.offset.x -= 0.1f;
		else if (keyState[SDL_SCANCODE_RIGHT] == 1)
			ball.offset.x += 0.1f;
	  
		renderer.clearScreen();
		renderer.render(ball);
		renderer.swapBuffers();
		
		}
	
	return 0;

	}

Let's try it out:

	cd build
	cmake --build .
	./bin/ball

For Windows:

	cd build
	cmake --build . --config Release
	.\bin\ball.exe

There's our ball:

![ball](https://cloud.githubusercontent.com/assets/875167/19624720/2fb6b99e-9904-11e6-885c-504ba726eeec.png)

Try moving it around with the arrows.

Important to remember about 3D models and textures
--------------------------------------------------

As we have seen, when exporting the models to Wavefront .obj files, we need to make sure we set the options "Write Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing, the normals listed later in the exported file for some vertices will overwrite the previous ones.

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


![Demo 2](https://cloud.githubusercontent.com/assets/875167/18656844/0dc828a0-7ef5-11e6-884b-706369d682f6.gif)
