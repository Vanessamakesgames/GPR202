#version 330 core

in vec4 vertexColour;

out vec4 pixelColour;

void main()
{
	pixelColour = vertexColour;
}