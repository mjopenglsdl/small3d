#version 330

smooth in float cosAngIncidence;
in vec2 textureCoords;
uniform sampler2D textureImage;
uniform vec4 colour;

out vec4 outputColour;

void main()
{
if (colour != vec4(0, 0, 0, 0)) {
    outputColour = cosAngIncidence * colour;
}
else {
  vec4 textureWtLight = cosAngIncidence * texture(textureImage, textureCoords);
  outputColour = vec4(textureWtLight.rgb, 1.0);
}

}
