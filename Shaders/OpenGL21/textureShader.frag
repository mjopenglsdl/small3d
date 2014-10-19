#version 120

varying float cosAngIncidence;
varying vec2 textureCoords;
uniform sampler2D textureImage;
uniform vec4 colour;

void main()
{
  if (colour != vec4(0, 0, 0, 0)) {
    gl_FragColor = cosAngIncidence * colour;
}
else {

  vec4 textureWtLight = cosAngIncidence * texture2D(textureImage, textureCoords);
  gl_FragColor = vec4(textureWtLight.rgb, 1.0);
}

}
