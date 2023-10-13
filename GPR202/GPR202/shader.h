#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <glew.h>
#include <stdbool.h>

typedef struct Shader
{
	GLuint programID;
} Shader;

Shader* shader_construct_shader_program(const char* _fileName);
void shader_activate_shader_program(GLuint _shaderProgramID);
void shader_delete_shader_program(GLuint _shaderProgramID);
void shader_set_uniform_1f(GLuint _shaderProgramID, const char* _uniformName, float _float);
void shader_set_uniform_2f(GLuint _shaderProgramID, const char* _uniformName, float _float1, float _float2);
void shader_set_uniform_3f(GLuint _shaderProgramID, const char* _uniformName, float _float1, float _float2, float _float3);
void shader_set_uniform_bool(GLuint _shaderProgramID, const char* _uniformName, bool _bool);
void shader_set_uniform_int(GLuint _shaderProgramID, const char* _uniformName, int _int);

// To implement later:
//void shader_set_uniform_vector2f(GLuint _shaderProgramID, const char* _uniformName, vec2(?) _vector);
//void shader_set_uniform_vector3f(GLuint _shaderProgramID, const char* _uniformName, vec3(?) _vector);
//void shader_set_uniform_vector4f(GLuint _shaderProgramID, const char* _uniformName, vec4(?) _vector);
//void shader_set_uniform_matrix4f(GLuint _shaderProgramID, const char* _uniformName, mat4(?) _matrix);

#endif