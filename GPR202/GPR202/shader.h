#ifndef SHADER_H
#define SHADER_H

#define GLEW_STATIC
#include <glew.h>
#include <stdbool.h>
#include <cglm/include/cglm/cglm.h>

typedef struct Shader
{
	GLuint programID;
} Shader;

Shader* shader_construct_shader_program(const char* _fileName);
void shader_activate_shader_program(GLuint _shaderProgramID);
void shader_deactivate_shader_program();
void shader_delete_shader_program(GLuint _shaderProgramID);
void shader_set_uniform_1f(GLuint _shaderProgramID, const char* _uniformName, float _float);
void shader_set_uniform_2f(GLuint _shaderProgramID, const char* _uniformName, float _float1, float _float2);
void shader_set_uniform_3f(GLuint _shaderProgramID, const char* _uniformName, float _float1, float _float2, float _float3);
void shader_set_uniform_vec2(GLuint _shaderProgramID, const char* _uniformName, vec2 _vec);
void shader_set_uniform_vec3(GLuint _shaderProgramID, const char* _uniformName, vec3 _vec);
void shader_set_uniform_vec4(GLuint _shaderProgramID, const char* _uniformName, vec4 _vec);
void shader_set_uniform_bool(GLuint _shaderProgramID, const char* _uniformName, bool _bool);
void shader_set_uniform_int(GLuint _shaderProgramID, const char* _uniformName, int _int);
void shader_set_uniform_mat4(GLuint _shaderProgramID, const char* _uniformName, mat4 _matrix);

#endif