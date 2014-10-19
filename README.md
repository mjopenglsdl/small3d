small3d
=======

A small, no fuss, 3D game engine


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

