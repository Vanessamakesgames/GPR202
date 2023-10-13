#version 330 core

layout (location = 0) in vec3 vertexPositionIn;
layout (location = 1) in vec3 vertexNormalIn;
layout (location = 2) in vec4 vertexColourIn;
layout (location = 3) in vec2 vertexUVCoordinatesIn;

out vec3 vertexPosition;
out vec3 vertexNormal;
out vec4 vertexColour;
out vec2 vertexUVCoordinates;

// add uniforms for mat4s once program has capacity for them

void main()
{
	vertexPosition = vertexPositionIn;
	vertexNormal = vertexNormalIn;
	vertexColour = vertexColourIn;
	vertexUVCoordinates = mat2(0.0, -1.0, 1.0, 0.0) * vertexUVCoordinatesIn;
	gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0);
}