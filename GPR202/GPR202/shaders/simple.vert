#version 330 core

layout (location = 0) in vec3 vertexPositionIn;
layout (location = 1) in vec4 vertexColourIn;

out vec3 vertexPosition;
out vec4 vertexColour;

// add uniforms for mat4s once program has capacity for them

void main()
{
	vertexPosition = vertexPositionIn;
	vertexColour = vertexColourIn;
	gl_Position = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
}