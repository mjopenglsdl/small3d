#version 120

attribute vec4 position;
attribute vec3 normal;
attribute vec2 uvCoords;

uniform vec3 offset;
uniform mat4 perspectiveMatrix;
uniform mat4 xRotationMatrix;
uniform mat4 yRotationMatrix;
uniform mat4 zRotationMatrix;

uniform vec3 cameraPosition;

uniform mat4 xCameraRotationMatrix;
uniform mat4 yCameraRotationMatrix;
uniform mat4 zCameraRotationMatrix;

uniform vec3 lightDirection;

varying float cosAngIncidence;
varying vec2 textureCoords;

void main()
{
    vec4 worldPos = position * zRotationMatrix * xRotationMatrix 
			* yRotationMatrix
			+ vec4(offset.x, offset.y, offset.z, 0.0);

    vec4 cameraPos = (worldPos - vec4(cameraPosition.x, cameraPosition.y, cameraPosition.z, 0.0))
		     * zCameraRotationMatrix
                     * xCameraRotationMatrix
                     * yCameraRotationMatrix;

    gl_Position = perspectiveMatrix * cameraPos;

    vec4 normalInWorld = vec4(normal, 1) * zRotationMatrix * xRotationMatrix 
			* yRotationMatrix;
    vec4 normalInCamera = normalInWorld * zCameraRotationMatrix
                     * xCameraRotationMatrix
                     * yCameraRotationMatrix;

    vec4 normalCameraSpace = normalize(perspectiveMatrix * normalInCamera);    
    
    vec4 lightDirectionCameraSpace = normalize(perspectiveMatrix * vec4(lightDirection, 1)  * zCameraRotationMatrix
                     * xCameraRotationMatrix
                     * yCameraRotationMatrix);

    cosAngIncidence = clamp(dot(normalCameraSpace, lightDirectionCameraSpace), 0, 1);
    textureCoords = uvCoords;
    
}
