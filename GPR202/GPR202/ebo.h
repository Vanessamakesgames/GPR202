#ifndef EBO_H
#define EBO_H

#define GLEW_STATIC
#include <glew.h>

typedef struct EBO
{
	GLuint ID;
} EBO;

EBO ebo_construct_ebo(GLuint* _indices, int _numberOfIndices);
void ebo_bind(GLuint _eboID);
void ebo_unbind();
void ebo_delete(EBO* _ebo);

#endif