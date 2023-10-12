#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include "texture.h"

typedef struct Mesh
{
	Vertex* vertices;
	GLuint* indices;
	Texture* textures;
} Mesh;

Mesh* mesh_construct_mesh(Vertex* _vertices, int _numberOfVertices, GLuint* _indices, int _numberOfIndices, Texture* _textures, int _numberOfTextures);

#endif