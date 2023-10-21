#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#define GLEW_STATIC
#include <glew.h>

typedef struct Mesh
{
	Vertex* vertices;
	int numberOfVertices;
	GLuint* indices;
	int numberOfIndices;
	GLuint vaoID;
	mat4 translation;
	mat4 rotation;
	mat4 scale;
} Mesh;

Mesh* mesh_construct_mesh(Vertex _vertices[], int _numberOfVertices, GLuint _indices[], int _numberOfIndices);
Mesh* mesh_construct_circle_mesh(float _radius, int _numberOfVertices);
void mesh_translate(Mesh* _mesh, vec3 _translation);
void mesh_rotate(Mesh* _mesh, vec3 _rotation);
void mesh_scale(Mesh* _mesh, vec3 _scale);
GLuint mesh_construct_vao();
GLuint mesh_construct_vbo(Vertex _vertices[], int _numberOfVertices);
GLuint mesh_construct_ebo(GLuint _indices[], int _numberOfIndices);
void mesh_link_attributes(GLuint _layout, GLuint _numberOfComponents, GLenum _type, GLboolean _normalised, GLsizeiptr _stride, void* _offset);
void mesh_bind_vao(GLuint _vaoID);
void mesh_unbind_vao();
void mesh_delete_vao(GLuint _vaoID);
void mesh_bind_buffer(GLenum _bufferType, GLuint _bufferID);
void mesh_unbind_buffer(GLenum _bufferType);
void mesh_delete_buffer(GLuint _bufferID);


#endif