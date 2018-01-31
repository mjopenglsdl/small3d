#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uvCoords;

layout(location = 0) smooth out float cosAngIncidence;
layout(location = 1) out vec2 textureCoords;

layout(location = 2) uniform positioning {
  vec3 offset;
  mat4 perspectiveMatrix;
  mat4 xRotationMatrix;
  mat4 yRotationMatrix;
  mat4 zRotationMatrix;
  vec3 cameraPosition;
  mat4 xCameraRotationMatrix;
  mat4 yCameraRotationMatrix;
  mat4 zCameraRotationMatrix;
  vec3 lightDirection;
};

void main()
{
  vec4 worldPos = position * zRotationMatrix * xRotationMatrix 
    * yRotationMatrix
    + vec4(offset.x, offset.y, offset.z, 0.0);

  vec4 cameraPos = (worldPos - vec4(cameraPosition.x, cameraPosition.y, cameraPosition.z, 0.0))
    * yCameraRotationMatrix * xCameraRotationMatrix * zCameraRotationMatrix;

  gl_Position = perspectiveMatrix * cameraPos;

  vec4 normalInWorld = normalize(perspectiveMatrix * (vec4(normal, 1) * zRotationMatrix * xRotationMatrix 
						      * yRotationMatrix));   
    
  vec4 lightDirectionWorld = normalize(perspectiveMatrix * vec4(lightDirection, 1));

  cosAngIncidence = clamp(dot(normalInWorld, lightDirectionWorld), 0, 1);
  textureCoords = uvCoords;
}
