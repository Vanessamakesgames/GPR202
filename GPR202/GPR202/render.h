#ifndef RENDER_H
#define RENDER_H

#include "shader.h"
#include "mesh.h"

void render(GLuint _shaderProgramID, Mesh* _meshBeingRendered, int _sizeOfIndices);

#endif