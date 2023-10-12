#include "Mesh.h"

#include <stdlib.h>

Mesh* mesh_construct_mesh(Vertex* _vertices, int _numberOfVertices, GLuint* _indices, int _numberOfIndices, Texture* _textures, int _numberOfTextures)
{
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->vertices = (Vertex*)malloc(sizeof(Vertex) * _numberOfVertices);
	mesh->indices = (GLuint*)malloc(sizeof(GLuint) * _numberOfIndices);
	mesh->textures = (Texture*)malloc(sizeof(Texture) * _numberOfTextures);

	for (int i = 0; i < _numberOfVertices; i++)
	{
		mesh->vertices[i] = _vertices[i];
	}

	for (int i = 0; i < _numberOfIndices; i++)
	{
		mesh->indices[i] = _indices[i];
	}

	for (int i = 0; i < _numberOfTextures; i++)
	{
		mesh->textures[i] = _textures[i];
	}

	return mesh;
}