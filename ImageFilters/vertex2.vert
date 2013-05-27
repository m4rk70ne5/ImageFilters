#version 430

layout(location = 0) in vec4 position; //input vertex coordinates
layout(location = 1) in vec2 vTexCoord; //input texture coordinates
uniform mat4 projectionMatrix;
out vec2 gTexCoord;

void main()
{
	gl_Position = projectionMatrix * position;
	// vec2 modPosition = position.xy / 1024.0f;
	// gl_Position = vec4(modPosition, 0.0f, 1.0f);
	gTexCoord = vTexCoord;
}