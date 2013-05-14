#version 430

layout(location = 0) in vec4 position; //input vertex coordinates
layout(location = 1) inout vec2 texCoord; //input texture coordinates
uniform mat4 projectionMatrix;

void main()
{
	gl_Position = projectionMatrix * position;
}