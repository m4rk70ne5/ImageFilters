#version 430

layout(location = 0) in vec4 position; //input vertex coordinates
layout(location = 1) in vec2 vTexCoord; //input texture coordinates
uniform mat4 projectionMatrix;
smooth out vec2 gTexCoord;

void main()
{
	gl_Position = projectionMatrix * position;
	gTexCoord = vTexCoord;
}