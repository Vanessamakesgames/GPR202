#version 330 core

layout (location = 0) in vec3 vertexPositionIn;
layout (location = 1) in vec4 vertexColourIn;

out vec4 vertexColour;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 scaleMatrix;
uniform mat4 viewMatrix;

void main()
{
	mat4 model = translationMatrix * rotationMatrix * scaleMatrix;
	vertexColour = vertexColourIn;
	gl_Position = viewMatrix * model * vec4(vertexPositionIn.x, vertexPositionIn.y, vertexPositionIn.z, 1.0);
}