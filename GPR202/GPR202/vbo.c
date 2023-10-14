#include "vbo.h"

#include "vertex.h"
#include <stdio.h>

VBO vbo_construct_vbo(Vertex** _vertices, int _numberOfVertices)
{
	VBO vbo;
	glGenBuffers(1, &vbo.ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
	glBufferData(GL_ARRAY_BUFFER, _numberOfVertices * sizeof(Vertex), &_vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//printf("x = %.1f, y = %.1f, z = %.1f\n", *_vertices->position.x)
	for (int i = 0; i < _numberOfVertices; i++)
	{
		printf("vbo_construct_vbo: index = %d, value in _vertices[%d]->position.x = %.1f, value in _vertices[%d]->position.y = %.1f, value in _vertices[%d]->position.z = %.1f\n", i, i, _vertices[i]->position->x, i, _vertices[i]->position->y, i, _vertices[i]->position->z);
	}

	return vbo;
}

void vbo_bind(GLuint _vboID)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
}

void vbo_unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_delete(VBO* vbo)
{
	glDeleteBuffers(1, vbo->ID);
}