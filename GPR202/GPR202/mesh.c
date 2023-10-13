#include "Mesh.h"

#include <stdlib.h>
#include <stdio.h>

/*Mesh**/void mesh_construct_mesh(Vertex* _vertices, int _numberOfVertices, GLuint* _indices, int _numberOfIndices/*, Texture* _textures, int _numberOfTextures*/)
{
	/*Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->vertices = (Vertex*)malloc(sizeof(Vertex) * _numberOfVertices);
	mesh->indices = (GLuint*)malloc(sizeof(GLuint) * _numberOfIndices);*/
	//mesh->textures = (Texture*)malloc(sizeof(Texture) * _numberOfTextures);
	//mesh->vertices = _vertices;

	for (int i = 0; i < _numberOfVertices; i++)
	{
		//mesh->vertices = _vertices;
		//printf("mesh_construct_mesh: vertices at index %d, x = %.1f, y = %.1f, z = %.1f\n", i, mesh->vertices->position->x, mesh->vertices->position->y, mesh->vertices->position->z);
		printf("mesh_construct_mesh: _vertices at index %d, x = %.1f, y = %.1f, z = %.1f\n", i, &_vertices[i].position->x, &_vertices[i].position->y, &_vertices[i].position->z);
		//mesh->vertices++;
		//_vertices++;
	}
	printf("\n");
	for (int i = 0; i < _numberOfIndices; i++)
	{
		//mesh->indices[i] = _indices[i];
		//printf("mesh_construct_mesh: indices at index %d, %d\n", i, mesh->indices[i]);
		printf("mesh_construct_mesh: _indices at index %d, %d\n", i, _indices[i]);
	}
	printf("\n");
	/*for (int i = 0; i < _numberOfTextures; i++)
	{
		mesh->textures[i] = _textures[i];
		printf("texture index %d\n", i);
	}*/

	printf("all here");

	//return mesh;
}

void mesh_cleanup(Mesh* _mesh)
{
	//free(_mesh->vertices);
	//free(_mesh->indices);
	//free(_mesh->textures);
	//free(_mesh);
}