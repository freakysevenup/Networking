#version 430 core
layout(location = 0) in vec4 vPosition;

uniform mat4 camera;
uniform mat4 model;

void main()
{
	gl_Position = (camera * model) * vPosition;
}
