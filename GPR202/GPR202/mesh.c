#include "mesh.h"
#include <stdlib.h>
#include <math.h>

// generic mesh constructor
Mesh* mesh_construct_mesh(Vertex _vertices[], int _numberOfVertices, GLuint _indices[], int _numberOfIndices)
{
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->vertices = (Vertex*)malloc(sizeof(Vertex) * _numberOfVertices);
	mesh->indices = (GLuint*)malloc(sizeof(GLuint) * _numberOfIndices);
	mesh->vertices = _vertices;
	mesh->indices = _indices;
	mesh->numberOfVertices = _numberOfVertices;
	mesh->numberOfIndices = _numberOfIndices;

	glm_mat4_identity(mesh->translation);
	glm_mat4_identity(mesh->rotation);
	glm_mat4_identity(mesh->scale);

	mesh->vaoID = mesh_construct_vao();
	GLuint vbo = mesh_construct_vbo(mesh->vertices, mesh->numberOfVertices);
	GLuint ebo = mesh_construct_ebo(mesh->indices, mesh->numberOfIndices);

	mesh_bind_buffer(GL_ARRAY_BUFFER, vbo);
	mesh_link_attributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	mesh_link_attributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));

	mesh_unbind_vao();
	mesh_unbind_buffer(GL_ARRAY_BUFFER);
	mesh_unbind_buffer(GL_ELEMENT_ARRAY_BUFFER);

	return mesh;
}

// circle mesh constructor
Mesh* mesh_construct_circle_mesh(float _radius, int _numberOfVertices)
{
	const float PI = 3.1415926f;
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->vertices = (Vertex*)malloc(sizeof(Vertex) * _numberOfVertices);
	int numberOfTriangles = _numberOfVertices - 2;
	mesh->numberOfVertices = _numberOfVertices;
	mesh->numberOfIndices = numberOfTriangles * 3;
	mesh->indices = (GLuint*)malloc(sizeof(GLuint) * mesh->numberOfIndices);
	float theta = 360 / _numberOfVertices;
	const double convertDegreesToRadians = PI / 180;

	glm_mat4_identity(mesh->translation);
	glm_mat4_identity(mesh->rotation);
	glm_mat4_identity(mesh->scale);
	
	for (int i = 0; i < _numberOfVertices; i++)
	{
		float x = _radius * cosf(i * (theta * convertDegreesToRadians));
		float y = _radius * sinf(i * (theta * convertDegreesToRadians));

		float red = 0.0f;
		float green = 0.0f;
		float blue = 0.0f;
		if (i % 3 == 0)
		{
			red = 1.0f;
			green = 0.5f;
		}
		if (i % 3 == 1)
		{
			green = 1.0f;
			blue = 0.5f;
		}
		else
		{
			blue = 1.0f;
			red = 0.5f;
		}
		Vertex vert = { .position = {x, y, 1.0}, .colour = {red, green, blue, 1.0} };
		mesh->vertices[i] = vert;
	}

	for (int i = 0; i < numberOfTriangles; i++)
	{
		mesh->indices[i * 3] = 0;
		mesh->indices[(i * 3) + 1] = i + 1;
		mesh->indices[(i * 3) + 2] = i + 2;
	}

	mesh->vaoID = mesh_construct_vao();
	GLuint vbo = mesh_construct_vbo(mesh->vertices, mesh->numberOfVertices);
	GLuint ebo = mesh_construct_ebo(mesh->indices, mesh->numberOfIndices);

	mesh_bind_buffer(GL_ARRAY_BUFFER, vbo);
	mesh_link_attributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	mesh_link_attributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));

	mesh_unbind_vao();
	mesh_unbind_buffer(GL_ARRAY_BUFFER);
	mesh_unbind_buffer(GL_ELEMENT_ARRAY_BUFFER);
	
	return mesh;
}

// slightly better circle mesh constructor
Mesh* mesh_construct_better_circle_mesh(float _radius, int _numberOfVertices)
{
	const float PI = 3.1415926f;
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->vertices = (Vertex*)malloc(sizeof(Vertex) * _numberOfVertices + 1);
	int numberOfTriangles = _numberOfVertices;
	mesh->numberOfVertices = _numberOfVertices + 1;
	mesh->numberOfIndices = numberOfTriangles * 3;
	mesh->indices = (GLuint*)malloc(sizeof(GLuint) * mesh->numberOfIndices);
	float theta = 360 / _numberOfVertices;
	const double convertDegreesToRadians = PI / 180;

	glm_mat4_identity(mesh->translation);
	glm_mat4_identity(mesh->rotation);
	glm_mat4_identity(mesh->scale);

	float red = 0.25f;
	float green = 0.5f;
	float blue = 0.75f;

	Vertex centerVert = { .position = {0.0, 0.0, 1.0,}, .colour = {red, green, blue, 1.0} };
	mesh->vertices[0] = centerVert;

	for (int i = 0; i < _numberOfVertices; i++)
	{
		float x = _radius * cosf(i * (theta * convertDegreesToRadians));
		float y = _radius * sinf(i * (theta * convertDegreesToRadians));

		red += 0.25f;
		if (red > 1.0) red = 0.0f;
		green += 0.25f;
		if (green > 1.0f) green = 0.0f;
		blue += 0.25;
		if (blue > 1.0f) blue = 0.0f;

		Vertex vert = { .position = {x, y, 1.0}, .colour = {red, green, blue, 1.0} };
		mesh->vertices[i + 1] = vert;
	}

	for (int i = 0; i < numberOfTriangles; i++)
	{
		mesh->indices[i * 3] = 0;
		mesh->indices[(i * 3) + 1] = i + 1;
		if (i == numberOfTriangles - 1) mesh->indices[(i * 3) + 2] = 1;
		else mesh->indices[(i * 3) + 2] = i + 2;
	}

	mesh->vaoID = mesh_construct_vao();
	GLuint vbo = mesh_construct_vbo(mesh->vertices, mesh->numberOfVertices);
	GLuint ebo = mesh_construct_ebo(mesh->indices, mesh->numberOfIndices);

	mesh_bind_buffer(GL_ARRAY_BUFFER, vbo);
	mesh_link_attributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	mesh_link_attributes(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(4 * sizeof(float)));

	mesh_unbind_vao();
	mesh_unbind_buffer(GL_ARRAY_BUFFER);
	mesh_unbind_buffer(GL_ELEMENT_ARRAY_BUFFER);

	return mesh;
}

void mesh_translate(Mesh* _mesh, vec3 _translation)
{
	glm_translate(_mesh->translation, _translation);
}

void mesh_rotate(Mesh* _mesh, vec3 _rotation)
{
	mat4 rotationX;
	mat4 rotationY;
	mat4 rotationZ;
	glm_mat4_identity(rotationX);
	glm_mat4_identity(rotationY);
	glm_mat4_identity(rotationZ);
	vec3 xRotAxis = {1.0f, 0.0f, 0.0f};
	vec3 yRotAxis = {0.0f, 1.0f, 0.0f};
	vec3 zRotAxis = {0.0f, 0.0f, 1.0f};
	const float PI = 3.1415926f;
	const double convertDegreesToRadians = PI / 180;

	glm_rotate(rotationX, _rotation[0] * convertDegreesToRadians, xRotAxis);
	glm_rotate(rotationY, _rotation[1] * convertDegreesToRadians, yRotAxis);
	glm_rotate(rotationZ, _rotation[2] * convertDegreesToRadians, zRotAxis);

	mat4 rotationResult;
	glm_mat4_identity(rotationResult);

	glm_mat4_mul(rotationZ, rotationY, rotationResult);
	glm_mat4_mul(rotationResult, rotationX, rotationResult);

	glm_mat4_copy(rotationResult, _mesh->rotation);
}

void mesh_scale(Mesh* _mesh, vec3 _scale)
{
	glm_scale(_mesh->scale, _scale);
}

GLuint mesh_construct_vao()
{
	GLuint ID;
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
	return ID;
}

GLuint mesh_construct_vbo(Vertex _vertices[], int _numberOfVertices)
{
	GLuint ID;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, _numberOfVertices * sizeof(Vertex), _vertices, GL_STATIC_DRAW);
	return ID;
}

GLuint mesh_construct_ebo(GLuint _indices[], int _numberOfIndices)
{
	GLuint ID;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberOfIndices * sizeof(GLuint), _indices, GL_STATIC_DRAW);
	return ID;
}

void mesh_link_attributes(GLuint _layout, GLuint _numberOfComponents, GLenum _type, GLboolean _normalised, GLsizeiptr _stride, void* _offset)
{
	glEnableVertexAttribArray(_layout);
	glVertexAttribPointer(_layout, _numberOfComponents, _type, _normalised, _stride, _offset);
}

void mesh_bind_vao(GLuint _vaoID)
{
	glBindVertexArray(_vaoID);
}

void mesh_unbind_vao()
{
	glBindVertexArray(0);
}

void mesh_delete_vao(GLuint _vaoID)
{
	glDeleteVertexArrays(1, _vaoID);
}

void mesh_bind_buffer(GLenum _bufferType, GLuint _bufferID)
{
	glBindBuffer(_bufferType, _bufferID);
}

void mesh_unbind_buffer(GLenum _bufferType)
{
	glBindBuffer(_bufferType, 0);
}

void mesh_delete_buffer(GLuint _bufferID)
{
	glDeleteBuffers(1, _bufferID);
}