#version 120

attribute vec4 position;
attribute vec3 normal;
attribute vec2 uvCoords;

uniform vec3 offset;
uniform mat4 perspectiveMatrix;
uniform mat4 xRotationMatrix;
uniform mat4 yRotationMatrix;
uniform mat4 zRotationMatrix;
uniform vec3 lightDirection;

varying float cosAngIncidence;
varying vec2 textureCoords;

void main()
{
    vec4 cameraPos = vec4(position) * zRotationMatrix * xRotationMatrix 
			* yRotationMatrix
			+ vec4(offset.x, offset.y, offset.z, 0.0);

    gl_Position = perspectiveMatrix * cameraPos;

    vec4 normalRotated = vec4(normal, 1) * zRotationMatrix * xRotationMatrix 
			* yRotationMatrix;

    vec4 normalCameraSpace = normalize(perspectiveMatrix * normalRotated);    
    
    vec4 lightDirectionCameraSpace = normalize(perspectiveMatrix * vec4(lightDirection, 1));

    cosAngIncidence = clamp(dot(normalCameraSpace, lightDirectionCameraSpace), 0, 1);
    textureCoords = uvCoords;
    
}
