#version 430 core

out vec4 fColor;

uniform vec4 colour;

void main()
{
	fColor = colour;
}