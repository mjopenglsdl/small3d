small3d
=======
[![Build status](https://ci.appveyor.com/api/projects/status/vl7gmu89v7194o2t?svg=true)](https://ci.appveyor.com/project/coding3d/small3d) [![Build Status](https://travis-ci.org/dimi309/small3d.svg?branch=master)](https://travis-ci.org/dimi309/small3d) [![Documentation](https://codedocs.xyz/dimi309/small3d.svg)](https://codedocs.xyz/dimi309/small3d/) [![badge](https://img.shields.io/badge/conan.io-small3d%2F1.0.8-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/small3d/1.0.8/coding3d/stable)

![beaver](https://raw.githubusercontent.com/coding3d/small3d/develop/assets/small3d.png)

Introduction
------------

![Demo 1](https://cloud.githubusercontent.com/assets/875167/18656425/4781b3d0-7ef1-11e6-83de-e412d5840fec.gif)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. I developed it while learning how to program games with OpenGL and I am still using it for my projects and experiments.

A Bit of History
----------------

*You don't need to read this to use the engine. Skip it if you're not interested.*

I'm a hoybbyist and permanent beginner in game development. I had always wanted to make games since I was a kid but, even though I have been working in IT for years, mostly as a developer, my work has nothing to do with games, graphics or anything of the sort.

A couple of years ago I thought that if I want to learn how to do this I might as well start. I'm interested in programming so I did not opt for a ready-made game engine. I get it that this is how most game development is carried out today and that it is a bad business decision to program everything by hand. I probably wouldn't do so if my income depended on it. If I understand it correctly, professionals who do write their own rendering logic or physics algorithms end up specialising in one specific area. Those who actually develop entire games just pick a multi-featured tool and study how to use it rather than how to push vertices to the GPU.

As I've mentioned, I was not looking to start a new career so I thought to proceed the way my 80s heroes would, writing code in their living rooms. So I started making a little game in which a bug is chasing a goat. Some have told me that the bug looks like a crow and the goat looks like a unicorn, which is understandable, since I'm also doing my own 3D modelling with Blender. Once the game was finished, I thought to put the functionality that could be reused in a library and this is how the small3d engine came to be.

One question I got at some point was why I did not follow the advice, "write games not engines". I've found a copy of the [article that says this](http://www.geometrian.com/programming/tutorials/write-games-not-engines/index.php) and I'm not sure that the author meant "just download an engine and get started". What I've done is not so far off from what he proposes, even though I may have been in a bit of a rush. But then again, I think it's good to be building a toolset of reusable items whenever you are working on something, no matter how much you have progressed.

Features
--------

- Runs on Windows, Mac, Linux (I'm using Debian and somebody told me that it works ok on Ubuntu, too).
- Uses OpenGL 3.3 and defaults to 2.1 if the former is not available. So, it comes with two sets of shaders.
- Uses C++11.
- You can tweak the engine's shaders, as long as you keep the same incoming variables and uniforms.
- Plays sounds from .ogg files.
- Doesn't hide SDL or OpenGL from you. You can set up your main game loop, inputs, etc, however you want and you can load your own shaders and make your own OpenGL calls if you want to do something that is not covered by the engine's features.
- It can read and render Wavefront files, including animations. For other formats, you can write your own reader, inherriting from the [ModelLoader](https://codedocs.xyz/dimi309/small3d/classsmall3d_1_1ModelLoader.html) class.
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
The best way to get started is to take a look at the source code of the sample games:

- [Avoid the Bug 3D](https://github.com/dimi309/AvoidTheBug3D)
- [Chase the Goat 3D](https://github.com/dimi309/ChaseTheGoat3D)

You can experiment by modifying them before using the engine for your own projects. You can also review the [API documentation](https://codedocs.xyz/dimi309/small3d/).

As can be seen from the games, the proposed way to use the engine is to deploy it from conan.io.

The engine is also available on [cppan](https://cppan.org/pvt.coding3d.small3d). An example of how it can be used from there can be found [here](https://github.com/dimi309/small3d-cppan-example).

If you prefer to compile it from source code, there are [instructions](BUILDING.md) about how to do this, but it is quite an involved procedure. I will always make sure that the engine can be built this way though.

3D models and textures
----------------------

As already mentioned, the engine can only read 3D models from Wavefront .obj files. There are many ways to create such a file, but I am exporting them from Blender.

When exporting the models to Wavefront .obj files, make sure you set the options "Include Normals", "Triangulate Faces", and "Keep Vertex Order". Only one object should be exported to each Wavefront file, because the engine cannot read more than one. The model has to have been set to have smooth shading in Blender and double vertices have to have been deleted before the export. Otherwise, when rendering with shaders, lighting will not work, since there will be multiple normals for each vertex and, with indexed drawing,
the normals listed later in the exported file for some vertices will overwrite the previous ones.

If a texture has been created, the option "Include UVs" must also be set. The texture should be saved as a PNG file, since this is the format that can be read by the program.

Collision Detection
-------------------

The engine supports collision detection via manually created bounding boxes. In order to create these in Blender for example, just place them in the preferred position over the model. Ideally, they should be aligned with the axes but that is not mandatory. It will just increase the detection accuracy.

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
