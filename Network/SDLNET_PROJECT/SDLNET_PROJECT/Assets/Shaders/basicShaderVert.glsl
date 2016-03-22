#version 430 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 textureCoords;
layout(location = 1) in vec3 normals;

out vec2 textureCoords0;
out vec3 normal0;

uniform mat4 camera;

void main(void)
{
	gl_Position = (camera * vec4(position, 1.0));
	textureCoords0 = textureCoords;
	normal0 = (camera * vec4(normals.xyz, 0.0)).xyz;
}