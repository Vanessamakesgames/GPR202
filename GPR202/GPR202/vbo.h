#ifndef VBO_H
#define VBO_H

#define GLEW_STATIC
#include <glew.h>
#include "vertex.h"

typedef struct VBO
{
	GLuint ID;
} VBO;

VBO vbo_construct_vbo(Vertex** _vertices, int _numberOfVertices);
void vbo_bind(GLuint _vboID);
void vbo_unbind();
void vbo_delete(VBO* vbo);
#endif