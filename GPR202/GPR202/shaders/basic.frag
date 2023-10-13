#version 330 core

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexColour;
in vec2 vertexUVCoordinates;

out vec4 pixelColour;

void main()
{
	pixelColour = vertexColour;
}