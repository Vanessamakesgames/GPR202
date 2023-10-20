#include <stdio.h>
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
//#include <time.h>
#include <stdbool.h>
#include <cglm/include/cglm/cglm.h>
#include <string.h>
#include <stdlib.h>
//#include "mesh.h"
//#include <stdlib.h>
//#include "shader.h"
//#include "render.h"

void glfw_onError(int error, const char* description)
{
	printf("GLFW error: %s\n", description);
}
void gl_debug_message_callback(GLenum unused, GLenum type, GLuint unused2, GLenum severity, GLsizei unused3, const GLchar* message, const void* unused4)
{
	if (severity > GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
		printf("%d\n", glGetError());
	}
}

typedef struct Vertex
{
	vec3 position;
	vec4 colour;
} Vertex;

typedef struct Mesh
{
	Vertex* vertices;
	int numberOfVertices;
	GLuint* indices;
	int numberOfIndices;
	GLuint vaoID;
} Mesh;

GLuint construct_vao()
{
	printf("Made it to construct vao\n");
	GLuint ID;
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
	return ID;
}

GLuint construct_vbo(Vertex _vertices[], int _numberOfVertices)
{
	printf("Made it to construct vbo\n");
	GLuint ID;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, _numberOfVertices * sizeof(Vertex), _vertices, GL_STATIC_DRAW);
	return ID;
}

GLuint construct_ebo(GLuint _indices[], int _numberOfIndices)
{
	GLuint ID;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numberOfIndices * sizeof(GLuint), _indices, GL_STATIC_DRAW);
	return ID;
}

GLuint construct_shaders(const char* _fileName)
{
	char* fileExtension = NULL;
	GLuint vertexShaderID, fragmentShaderID, shaderProgramID;
	
	{
#define BUFFER_SIZE 1024
		FILE* file = NULL;
		char buffer[BUFFER_SIZE];
		char* fileName = malloc(sizeof(_fileName) + 5);
		strcpy(fileName, _fileName);
		fileExtension = ".vert";
		fileName = strcat(fileName, fileExtension);
		printf("%s\n", fileName);
		file = fopen(fileName, "r");
		if (file == 0)
		{
			printf("Failed to open vertex shader file: %s\n", fileName);
			exit(1);
		}

		int bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file);
		buffer[bytesRead] = 0;
		printf("%s\n", buffer);
		fclose(file);
		
		const char* source_c_str = buffer;
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &source_c_str, NULL);
		glCompileShader(vertexShaderID);
		GLint shaderCompilationResult;
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &shaderCompilationResult);
		if (shaderCompilationResult == GL_FALSE)
		{
			GLchar info[1024];
			glGetShaderInfoLog(vertexShaderID, sizeof(info), NULL, info);
			printf("%s\n", info);
			exit(2);
		}
	}
	printf("Made it past vertex shader section\n");
	{
#define BUFFER_SIZE 1024
		FILE* file = NULL;
		char buffer[BUFFER_SIZE];
		char* fileName = malloc(sizeof(_fileName) + 5);
		strcpy(fileName, _fileName);
		fileExtension = ".frag";
		fileName = strcat(fileName, fileExtension);
		file = fopen(fileName, "r");
		if (file == 0)
		{
			printf("Failed to open fragment shader file: %s\n", fileName);
			exit(3);
		}

		int bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file);
		buffer[bytesRead] = 0;
		printf("%s\n", buffer);
		fclose(file);

		const char* source_c_str = buffer;
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &source_c_str, NULL);
		glCompileShader(fragmentShaderID);
		GLint shaderCompilationResult;
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &shaderCompilationResult);
		if (shaderCompilationResult == GL_FALSE)
		{
			GLchar info[1024];
			glGetShaderInfoLog(fragmentShaderID, sizeof(info), NULL, info);
			printf("%s\n", info);
			exit(4);
		}
	}
	printf("Made it past fragment shader section\n");
	{
		shaderProgramID = glCreateProgram();
		if (shaderProgramID == 0)
		{
			printf("Failed to create shader program\n");
			exit(5);
		}

		glAttachShader(shaderProgramID, vertexShaderID);
		glAttachShader(shaderProgramID, fragmentShaderID);
		glLinkProgram(shaderProgramID);

		GLint shaderProgramLinkingResult;
		glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &shaderProgramLinkingResult);
		if (shaderProgramLinkingResult == GL_FALSE)
		{
			GLchar info[1024];
			glGetProgramInfoLog(shaderProgramID, sizeof(info), NULL, info);
			printf("%s\n", info);
			exit(6);
		}
	}
	printf("Made it past shader program section\n");
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	printf("Made it to end of construct shaders\n");

	return shaderProgramID;
}

Mesh* construct_mesh(Vertex _vertices[], int _numberOfVertices, GLuint _indices[], int _numberOfIndices)
{
	printf("Made it to construct mesh\n");
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->vertices = (Vertex*)malloc(sizeof(Vertex) * _numberOfVertices);
	mesh->indices = (GLuint*)malloc(sizeof(GLuint) * _numberOfIndices);
	mesh->vertices = _vertices;
	mesh->indices = _indices;
	mesh->numberOfVertices = _numberOfVertices;
	mesh->numberOfIndices = _numberOfIndices;
	mesh->vaoID = construct_vao();
	GLuint vbo = construct_vbo(mesh->vertices, mesh->numberOfVertices);
	GLuint ebo = construct_ebo(mesh->indices, mesh->numberOfIndices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return mesh;
}

void render(GLuint _shaderProgramID, Mesh* _mesh)
{
	glUseProgram(_shaderProgramID);
	glBindVertexArray(_mesh->vaoID);
	glDrawElements(GL_TRIANGLES, _mesh->numberOfIndices, GL_UNSIGNED_INT, 0);
}

int main()
{
	// Initialize GLFW
	int glfwSuccess = glfwInit();
	if (glfwSuccess != GLFW_TRUE)
	{
		printf("GLFW initialization failed\n");
		return 1;
	}

	// Set up window for OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(512, 512, "Vanguard", NULL, NULL);
	if (window == NULL)
	{
		printf("GLFW failed to create window\n");
		return 2;
	}
	glfwMakeContextCurrent(window);

	// Set up glew
	glewExperimental = GL_TRUE;
	GLenum glewSuccess = glewInit();
	if (glewSuccess != GLEW_OK)
	{
		printf("glew initialization failed\n");
		printf("%s\n", glewGetErrorString(glewSuccess));
		return 3;
	}

	//	// OpenGL debugging
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_debug_message_callback, 0);
	glfwSetErrorCallback(glfw_onError);

	// Set up face culling
	glFrontFace(GL_CCW);

	// 3D stuff
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	Vertex vert1 = { .position = {1.0, 0.0, 1.0}, . colour = {1.0, 1.0, 0.0, 1.0} };
	Vertex vert2 = { .position = {0.0, 1.0, 1.0}, . colour = {0.0, 1.0, 1.0, 1.0} };
	Vertex vert3 = { .position = {-1.0, 0.0, 1.0}, . colour = {1.0, 0.0, 1.0, 1.0} };

	Vertex verts[3] = {vert1, vert2, vert3};
	GLuint indices[3] = { 0, 1, 2 };

	Mesh* mesh = construct_mesh(verts, 3, indices, 3);

	GLuint shaderID = construct_shaders("shaders/simple");

	bool gameplayLoop = true;
	
		while (gameplayLoop)
		{
			glfwSwapBuffers(window);
			glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
			glfwPollEvents();
			//updates
			//render
			render(shaderID, mesh);
			glBindVertexArray(0);
			glUseProgram(0);
		}

		return 0;
}

//
//int main(void)
//{
//	
//
//	// Initialize GLFW
//	int glfwSuccess = glfwInit();
//	if (glfwSuccess != GLFW_TRUE)
//	{
//		printf("GLFW initialization failed\n");
//		return 1;
//	}
//	
//	// Set up window for OpenGL 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	// Create window
//	GLFWwindow* window = glfwCreateWindow(512, 512, "Vanguard", NULL, NULL);
//	if (window == NULL)
//	{
//		printf("GLFW failed to create window\n");
//		return 2;
//	}
//	glfwMakeContextCurrent(window);
//
//	// Set up glew
//	glewExperimental = GL_TRUE;
//	GLenum glewSuccess = glewInit();
//	if (glewSuccess != GLEW_OK)
//	{
//		printf("glew initialization failed\n");
//		printf("%s\n", glewGetErrorString(glewSuccess));
//		return 3;
//	}
//
//	// OpenGL debugging
//	glEnable(GL_DEBUG_OUTPUT);
//	glDebugMessageCallback(gl_debug_message_callback, 0);
//	glfwSetErrorCallback(glfw_onError);
//
//	// Set up face culling
//	//glFrontFace(GL_CCW);
//
//	// 3D stuff
//	//glEnable(GL_DEPTH_TEST);
//	//glDepthFunc(GL_LESS);
//
//	//Vertex vertices[] = {};
//
//	//Mesh* firstMesh = mesh_construct_mesh()
//
//	//Vertex* v = vertex_construct_vertex(vertex_construct_position(1.0f, 1.0f, 1.0f), vertex_construct_normal(1.0f, 1.0f, 1.0f), vertex_construct_colour(1.0f, 1.0f, 1.0f, 1.0f), vertex_construct_uvcoord(1.0f, 1.0f));
//
//	/*Vertex* vert = vertex_construct_vertex(
//					vertex_construct_position(0.1f, 0.2f, 0.3f),
//					vertex_construct_normal(0.4f, 0.5f, 0.6f),
//					vertex_construct_colour(0.7f, 0.8f, 0.90f, 1.0f),
//					vertex_construct_uvcoord(1.1f, 1.2f)
//					);
//
//	free(vert);
//
//	Vertex verts[5] = {
//		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
//		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
//		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
//		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
//		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))}
//	};*/
//
//	Vertex* triangleVertices[3] = {
//		{vertex_construct_vertex(vertex_construct_position(-1.0f, -1.0f, 1.0f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.0f, 0.0f, 0.0f, 1.0f), vertex_construct_uvcoord(0.0f, 0.0f))},
//		{vertex_construct_vertex(vertex_construct_position(1.0f, -1.0f, 1.0f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.0f, 0.0f, 0.0f, 1.0f), vertex_construct_uvcoord(1.0f, 0.0f))},
//		{vertex_construct_vertex(vertex_construct_position(0.0f, 1.0f, 1.0f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.0f, 0.0f, 0.0f, 1.0f), vertex_construct_uvcoord(0.5f, 1.0f))}
//	};
//
//	GLuint triangleIndices[3] = { 0, 1, 2 };
//
//	Texture* triangleTextures[2] = { texture_construct_texture("textures/planks.png", "diffuse", 0), texture_construct_texture("textures/planksSpec.png", "specular", 1) };
//
//	/*printf("main: x = %.1f, y = %.1f, z = %.1f\n", triangleVertices[0]->position->x, triangleVertices[0]->position->y, triangleVertices[0]->position->z);
//	printf("main: x = %.1f, y = %.1f, z = %.1f\n", triangleVertices[1]->position->x, triangleVertices[1]->position->y, triangleVertices[1]->position->z);
//	printf("main: x = %.1f, y = %.1f, z = %.1f\n", triangleVertices[2]->position->x, triangleVertices[2]->position->y, triangleVertices[2]->position->z);*/
//
//	Mesh* triangleMesh = mesh_construct_mesh(triangleVertices, 3, triangleIndices, 3, triangleTextures, 2);
//
//	//VAO* vao = vao_construct_vao();
//	//VAO* vao2 = vao_construct_vao();
//
//	//mesh_cleanup(triangleMesh);
//	// having these causes errors?
//	//free(triangleMesh);
//	//free(triangleVertices);
//	//free(triangleTextures);
//	//free(triangleIndices);
//
//	Shader* basicShader = shader_construct_shader_program("shaders/basic");
//
//	bool gameplayLoop = true;
//
//	while (gameplayLoop)
//	{
//		glfwSwapBuffers(window);
//		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
//		glfwPollEvents();
//		//updates
//		//render
//		render(basicShader->programID, triangleMesh, 3);
//		glBindVertexArray(0);
//		glUseProgram(0);
//	}
//
//	//free(triangleMesh);
//
//	return 0;
//}