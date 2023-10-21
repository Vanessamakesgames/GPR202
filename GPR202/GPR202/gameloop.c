#include "gameloop.h"

#include <stdio.h>

void gameloop_update_mesh(GLuint _shaderProgramID, Mesh* _mesh, mat4 _viewMatrix)
{
	shader_activate_shader_program(_shaderProgramID);
	shader_set_uniform_mat4(_shaderProgramID, "translationMatrix", _mesh->translation);
	shader_set_uniform_mat4(_shaderProgramID, "rotationMatrix", _mesh->rotation);
	shader_set_uniform_mat4(_shaderProgramID, "scaleMatrix", _mesh->scale);
	shader_set_uniform_mat4(_shaderProgramID, "viewMatrix", _viewMatrix);
	shader_deactivate_shader_program();
}

void gameloop_render_mesh(GLuint _shaderProgramID, Mesh* _mesh)
{
	shader_activate_shader_program(_shaderProgramID);
	mesh_bind_vao(_mesh->vaoID);
	glDrawElements(GL_TRIANGLES, _mesh->numberOfIndices, GL_UNSIGNED_INT, 0);
}