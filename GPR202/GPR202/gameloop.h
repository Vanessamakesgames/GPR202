#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "shader.h"
#include "mesh.h"

void gameloop_update_mesh(GLuint _shaderProgramID, Mesh* _mesh, mat4 _viewMatrix);
void gameloop_render_mesh(GLuint _shaderProgramID, Mesh* _mesh);

#endif