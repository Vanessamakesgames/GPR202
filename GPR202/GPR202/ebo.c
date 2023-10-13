#include "ebo.h"

EBO ebo_construct_ebo(GLuint* _indices, int _numberOfIndices)
{
	EBO ebo;
	glGenBuffers(1, &ebo.ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberOfIndices * sizeof(GLuint), _indices, GL_STATIC_DRAW);
}

void ebo_bind(GLuint _eboID)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);
}

void ebo_unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ebo_delete(EBO* _ebo)
{
	glDeleteBuffers(1, _ebo->ID);
}