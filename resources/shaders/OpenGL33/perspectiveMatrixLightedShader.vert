#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uvCoords;

smooth out float cosAngIncidence;
out vec2 textureCoords;

uniform vec3 offset;
uniform mat4 perspectiveMatrix;

uniform mat4 xRotationMatrix;
uniform mat4 yRotationMatrix;
uniform mat4 zRotationMatrix;

uniform vec3 lightDirection;

void main()
{
    vec4 cameraPos = position * zRotationMatrix * xRotationMatrix 
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
