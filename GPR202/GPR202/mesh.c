//#include "mesh.h"
//
//#include <stdlib.h>
//#include <stdio.h>
//#include "vao.h"
//#include "ebo.h"
//
//Mesh* mesh_construct_mesh(Vertex** _vertices, int _numberOfVertices, GLuint* _indices, int _numberOfIndices, Texture** _textures, int _numberOfTextures)
//{
//	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
//	mesh->vertices = (Vertex*)malloc(sizeof(Vertex) * _numberOfVertices);
//	mesh->indices = (GLuint*)malloc(sizeof(GLuint) * _numberOfIndices);
//	mesh->textures = (Texture*)malloc(sizeof(Texture) * _numberOfTextures);
//	if (mesh->vertices == NULL) printf("mesh->vertices == NULL\n");
//	if (mesh->indices == NULL) printf("mesh->indices == NULL\n");
//	if (mesh->textures == NULL) printf("mesh->textures == NULL\n");
//
//	//for (int i = 0; i < _numberOfVertices; i++)
//	//{
//	//	mesh[i].vertices = _vertices[i];
//	//	printf("mesh_construct_mesh: vertices at index %d, x = %.1f, y = %.1f, z = %.1f\n", i, mesh[i].vertices->position->x, mesh[i].vertices->position->y, mesh[i].vertices->position->z);
//	//	printf("mesh_construct_mesh: _vertices at index %d, x = %.1f, y = %.1f, z = %.1f\n", i, _vertices[i]->position->x, _vertices[i]->position->y, _vertices[i]->position->z);
//	//	//mesh->vertices++;
//	//	//_vertices++;
//	//}
//	//printf("\n");
//	//for (int i = 0; i < _numberOfIndices; i++)
//	//{
//	//	mesh[i].indices = _indices[i];
//	//	printf("mesh_construct_mesh: indices at index %d, %d\n", i, mesh[i].indices);
//	//	printf("mesh_construct_mesh: _indices at index %d, %d\n", i, _indices[i]);
//	//}
//	//printf("\n");
//	//for (int i = 0; i < _numberOfTextures; i++)
//	//{
//	//	mesh[i].textures = _textures[i];
//	//	printf("texture index %d\n", i);
//	//}
//
//	for (int i = 0; i < _numberOfVertices; i++)
//	{
//		//mesh[i].vertices = _vertices[i];
//		mesh->vertices[i] = *_vertices[i];
//		printf("mesh_construct_mesh: vertices at index %d, x = %.1f, y = %.1f, z = %.1f\n", i, mesh->vertices[i].position->x, mesh->vertices[i].position->y, mesh->vertices[i].position->z);
//		printf("mesh_construct_mesh: _vertices at index %d, x = %.1f, y = %.1f, z = %.1f\n", i, _vertices[i]->position->x, _vertices[i]->position->y, _vertices[i]->position->z);
//		//mesh->vertices++;
//		//_vertices++;
//	}
//	printf("\n");
//	for (int i = 0; i < _numberOfIndices; i++)
//	{
//		mesh->indices[i] = _indices[i];
//		printf("mesh_construct_mesh: indices at index %d, %d\n", i, mesh->indices[i]);
//		printf("mesh_construct_mesh: _indices at index %d, %d\n", i, _indices[i]);
//	}
//	printf("\n");
//	for (int i = 0; i < _numberOfTextures; i++)
//	{
//		printf("got to textures\n");
//		mesh->textures[i] = *_textures[i];
//		printf("textures[%d].ID = %d, textures[%d].type = %s, textures[%d].slot = %d\n", i, mesh->textures[i].ID, i, mesh->textures[i].type, i, mesh->textures[i].slot);
//		printf("_textures[%d]->ID = %d, _textures[%d]->type = %s, _textures[%d]->slot = %d\n", i, _textures[i]->ID, i, _textures[i]->type, i, _textures[i]->slot);
//		printf("texture index %d\n", i);
//	}
//
//	printf("all here\n");
//
//	mesh->vao = vao_construct_vao();
//	printf("vao constructed?\nvao id = %d\n", mesh->vao.ID);
//
//	vao_bind(mesh->vao.ID);
//
//	VBO vbo = vbo_construct_vbo(_vertices, _numberOfVertices);
//	printf("end of vbo constructor\n");
//
//	EBO ebo = ebo_construct_ebo(_indices, _numberOfIndices);
//	printf("end of ebo constructor\n");
//
//	printf("start of link attrib funcs");
//	vao_link_attributes(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
//	vao_link_attributes(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
//	vao_link_attributes(vbo, 2, 4, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
//	vao_link_attributes(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(10 * sizeof(float)));
//	printf("end of link attrib funcs\n");
//
//	vao_unbind();
//	vbo_unbind();
//	ebo_unbind();
//
//	printf("vao, vbo and ebo unbound\n");
//
//	return mesh;
//}
//
//void mesh_cleanup(Mesh* _mesh)
//{
//	//free(_mesh->vertices);
//	//free(_mesh->indices);
//	//free(_mesh->textures);
//	//free(_mesh);
//}