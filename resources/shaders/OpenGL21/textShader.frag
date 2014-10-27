#version 120

varying vec2 textureCoords;
uniform sampler2D textureImage;

void main()
{

    gl_FragColor = texture2D(textureImage, textureCoords);
    //gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
