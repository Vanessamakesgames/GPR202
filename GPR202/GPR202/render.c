#include "render.h"

#include <stdio.h>

void render(GLuint _shaderProgramID, Mesh* _mesh, int _sizeOfIndices)
{
	shader_activate_shader_program(_shaderProgramID);
	vao_bind(_mesh->vao.ID);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}