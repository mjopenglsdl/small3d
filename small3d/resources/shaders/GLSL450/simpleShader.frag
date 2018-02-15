#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 textureCoords;
layout(location = 0) uniform sampler2D textureImage;

uniform surface {
  vec4 colour;
};

layout(location = 2) out vec4 outputColour;

void main()
{

  if (colour != vec4(0, 0, 0, 0)) {
    outputColour = vec4(colour.rgb, colour.a);
  }
  else {

    vec4 tcolour = texture(textureImage, textureCoords);
    outputColour = tcolour;

  }

}
