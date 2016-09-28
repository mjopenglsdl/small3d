small3d
=======
[![Build status](https://ci.appveyor.com/api/projects/status/vl7gmu89v7194o2t?svg=true)](https://ci.appveyor.com/project/coding3d/small3d) [![Build Status](https://travis-ci.org/dimi309/small3d.svg?branch=master)](https://travis-ci.org/dimi309/small3d) [![Documentation](https://codedocs.xyz/dimi309/small3d.svg)](https://codedocs.xyz/dimi309/small3d/) [![badge](https://img.shields.io/badge/conan.io-small3d%2F1.0.5-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/small3d/1.0.5/coding3d/stable)

![beaver](https://raw.githubusercontent.com/coding3d/small3d/develop/assets/small3d.png)

Introduction
------------

![Demo 1](https://cloud.githubusercontent.com/assets/875167/18656425/4781b3d0-7ef1-11e6-83de-e412d5840fec.gif)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL.

Getting Started
---------------
The best way to get started is to take a look at the source code of two provided sample games:

- [samples/AvoidTheBug3D](https://github.com/dimi309/small3d/tree/master/samples/AvoidTheBug3D)
- [samples/ChaseTheGoat3D](https://github.com/dimi309/small3d/tree/master/samples/ChaseTheGoat3D)

You can experiment by modifying them before using the engine for your own projects. You can also review the [API documentation](https://codedocs.xyz/dimi309/small3d/).

As can be seen from the sample games, the proposed way to use the engine is to link to it from [conan.io](https://www.conan.io/source/small3d/1.0.5/coding3d/stable).

The engine is also available on [cppan](https://cppan.org/pvt.coding3d.small3d). An example of how it can be used from there can be found [here](https://github.com/cppan/small3d_example).

If you prefer to compile it from the source code, there are [instructions](BUILDING.md) about how to do this, but it is quite an involved procedure. I will always make sure that the engine can be built this way though.

Compatibility
-------------
The engine has been successfully compiled and tested on Windows, OSX and Linux (Debian). It works with OpenGL 3.3, but will default to OpenGL 2.1 at runtime if the former is not available.

If you have any problems with the builds, or any questions and need help, don't hesitate to [open an issue](https://github.com/coding3d/small3d/issues).

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


![Demo 2](https://cloud.githubusercontent.com/assets/875167/18656844/0dc828a0-7ef5-11e6-884b-706369d682f6.gif)
