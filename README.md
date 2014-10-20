small3d 
=======
*A small, no fuss, 3D game engine*

![Screen capture from the first game that runs on small3d](https://dimitros.be/media/3DGameDevDiaryEntry11/AvoidTheBug3DWithTree.png)

This is a free, open-source, minimalistic 3D game engine, developed in C++ and based on modern OpenGL. It is meant for those who are in a hurry to produce something playable, but prefer to understand what is happening under the hood rather than use a technology that abstracts the low-level details away.

It has been derived from a simple game which has been under development for more than a year, as a learning exercise (introduction: http://goo.gl/itn6x5, blog: http://goo.gl/7hCTPA). I have decided to separate the engine from the game already, rather than finishing the project first. I think that this will help the engine mature faster and will simplify the development of the game.

What actually made me take the plunge though, was that I discovered the great C++ dependency management tool and service that is biicode :) So I have configured the engine’s files to be served from there (many thanks to the other biicode members who have set up the libraries I am using from there).

Over time, more information will be provided about this project and how it can be used, but here are some items to begin with:

API documentation: http://small3d.org

Block on biicode : http://www.biicode.com/dimitrikourk/dimitrikourk/small3d/master

Original branch of the game development project:
https://github.com/dimitrikourk/CrossPlatform3DLearning

biicode-adapted branch of the game development project, which now uses the engine:
https://github.com/dimitrikourk/CrossPlatform3DLearning/tree/biicode


Note about 3D models and textures
---------------------------------

For the time being, the engine can only read 3D
models from Wavefront .obj files. There are many
ways to create such a file, but I am exporting them
from Blender.

When exporting the models to Wavefront .obj files,
make sure you set the options "Include Normals",
"Triangulate Faces", and "Keep Vertex Order".
Only one object should be exported to each
Wavefront file, because the engine cannot read
more than one. The model has to have been set to
have smooth shading in Blender and double vertices
have to have been deleted before the export.
Otherwise, when rendering with shaders, lighting
will not work, since there will be multiple
normals for each vertex and, with indexed drawing,
the normals listed later in the exported file
for some vertices will overwrite the previous
ones.

If a texture has been created, the option "Include
UVs" must also be set. The texture should be saved
as a PNG file, since this is the format that can
be read by the program. The PNG file can have no
transparency information stored (in my case, in 
order to achieve this, I load it in Gimp, select 
Image > Flatten Image and then re-export it as a
PNG file from there).

The engine also supports manually created bounding
boxes for collision detection. In order to create
these in Blender for example, just place them in
the preferred position over the model and export
them to Wavefront separately from the model, only 
with the options "Apply Modifiers", "Include Edges",
"Objects as OBJ Objects" and "Keep Vertex Order".
On the contrary to what is the case when exporting
the model itself, more than one bounding box objects 
can be exported to the same Wavefront file.


