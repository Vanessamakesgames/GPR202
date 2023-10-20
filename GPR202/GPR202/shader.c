//#include "shader.h"
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//Shader* shader_construct_shader_program(const char* _fileName)
//{
//	Shader* shader = (Shader*)malloc(sizeof(Shader));
//
//	char* fileExtension = NULL;
//	
//	GLuint vertexShaderID, fragmentShaderID;
//
//	// vertex shader
//	{
//		#define BUFFER_SIZE 1024
//		FILE* file = NULL;
//		char buffer[BUFFER_SIZE];
//		char* fileName = malloc(sizeof(_fileName) + 5);
//		strcpy(fileName, _fileName);
//		fileExtension = ".vert";
//		fileName = strcat(fileName, fileExtension);
//		file = fopen(fileName, "r");
//		if (file == 0)
//		{
//			printf("Failed to open vertex shader file: %s\n", fileName);
//			exit(4);
//		}
//
//		int bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file);
//		buffer[bytesRead] = 0;
//		printf("%s\n", buffer);
//		fclose(file);
//
//		const char* source_c_str = buffer;
//		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
//		glShaderSource(vertexShaderID, 1, &source_c_str, NULL);
//		glCompileShader(vertexShaderID);
//
//		GLint shaderCompilationResult;
//		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &shaderCompilationResult);
//		if (shaderCompilationResult == GL_FALSE)
//		{
//			GLchar info[1024];
//			glGetShaderInfoLog(vertexShaderID, sizeof(info), NULL, info);
//			printf("%s\n", info);
//			exit(5);
//		}
//	}
//
//	printf("Made it past vertex shader section\n");
//
//	// fragment shader
//	{
//		#define BUFFER_SIZE 1024
//		FILE* file = NULL;
//		char buffer[BUFFER_SIZE];
//		char* fileName = malloc(sizeof(_fileName) + 5);
//		strcpy(fileName, _fileName);
//		fileExtension = ".frag";
//		fileName = strcat(fileName, fileExtension);
//		file = fopen(fileName, "r");
//		if (file == 0)
//		{
//			printf("Failed to open fragment shader file: %s\n", fileName);
//			exit(6);
//		}
//		
//		int bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file);
//		buffer[bytesRead] = 0;
//		printf("%s\n", buffer);
//		fclose(file);
//		//printf("Checkpoint 1\n");
//		
//		const char* source_c_str = buffer;
//		//printf("Checkpoint 2\n");
//		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
//		//printf("Checkpoint 3\n");
//		//printf("source: %s\n", source_c_str);
//		//printf("buffer: %s\n", buffer);
//		//printf("fShaderID: %d\n", fragmentShaderID);
//		glShaderSource(fragmentShaderID, 1, &source_c_str, NULL);
//		//printf("Checkpoint 4\n");
//		glCompileShader(fragmentShaderID);
//		//printf("Checkpoint 5\n");
//		GLint shaderCompilationResult;
//		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &shaderCompilationResult);
//		if (shaderCompilationResult == GL_FALSE)
//		{
//			GLchar info[1024];
//			glGetShaderInfoLog(fragmentShaderID, sizeof(info), NULL, info);
//			printf("%s\n", info);
//			exit(7);
//		}
//	}
//
//	printf("Made it past fragment shader section\n");
//
//	// Shader program
//	{
//		GLuint programID = glCreateProgram();
//		if (programID == 0)
//		{
//			printf("Failed to craete the shader program\n");
//			exit(8);
//		}
//
//		glAttachShader(programID, vertexShaderID);
//		glAttachShader(programID, fragmentShaderID);
//		glLinkProgram(programID);
//
//		GLint shaderProgramLinkingResult;
//		glGetProgramiv(programID, GL_LINK_STATUS, &shaderProgramLinkingResult);
//		if (shaderProgramLinkingResult == GL_FALSE)
//		{
//			GLchar info[1024];
//			glGetProgramInfoLog(programID, sizeof(info), NULL, info);
//			printf("%s\n", info);
//			exit(9);
//		}
//
//		shader->programID = programID;
//	}
//
//	printf("Made it past shader program section\n");
//
//	glDeleteShader(vertexShaderID);
//	glDeleteShader(fragmentShaderID);
//
//	return shader;
//}
//
//void shader_activate_shader_program(GLuint _shaderProgramID)
//{
//	glUseProgram(_shaderProgramID);
//}
//
//void shader_delete_shader_program(GLuint _shaderProgramID)
//{
//	glDeleteProgram(_shaderProgramID);
//}
//
//void shader_set_uniform_1f(GLuint _shaderProgramID, const char* _uniformName, float _float)
//{
//	glUniform1f(glGetUniformLocation(_shaderProgramID, _uniformName), _float);
//}
//
//void shader_set_uniform_2f(GLuint _shaderProgramID, const char* _uniformName, float _float1, float _float2)
//{
//	glUniform2f(glGetUniformLocation(_shaderProgramID, _uniformName), _float1, _float2);
//}
//
//void shader_set_uniform_3f(GLuint _shaderProgramID, const char* _uniformName, float _float1, float _float2, float _float3)
//{
//	glUniform3f(glGetUniformLocation(_shaderProgramID, _uniformName), _float1, _float2, _float3);
//}
//
//void shader_set_uniform_bool(GLuint _shaderProgramID, const char* _uniformName, bool _bool)
//{
//	glUniform1i(glGetUniformLocation(_shaderProgramID, _uniformName), (int)_bool);
//}
//
//void shader_set_uniform_int(GLuint _shaderProgramID, const char* _uniformName, int _int)
//{
//	glUniform1i(glGetUniformLocation(_shaderProgramID, _uniformName), _int);
//}