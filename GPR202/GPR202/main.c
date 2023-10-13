#include <stdio.h>
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <time.h>
#include <stdbool.h>
#include "mesh.h"
#include <stdlib.h>
#include "shader.h"
#include "render.h"

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

int main(void)
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

	// OpenGL debugging
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_debug_message_callback, 0);
	glfwSetErrorCallback(glfw_onError);

	// Set up face culling
	//glFrontFace(GL_CCW);

	// 3D stuff
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	//Vertex vertices[] = {};

	//Mesh* firstMesh = mesh_construct_mesh()

	//Vertex* v = vertex_construct_vertex(vertex_construct_position(1.0f, 1.0f, 1.0f), vertex_construct_normal(1.0f, 1.0f, 1.0f), vertex_construct_colour(1.0f, 1.0f, 1.0f, 1.0f), vertex_construct_uvcoord(1.0f, 1.0f));

	/*Vertex* vert = vertex_construct_vertex(
					vertex_construct_position(0.1f, 0.2f, 0.3f),
					vertex_construct_normal(0.4f, 0.5f, 0.6f),
					vertex_construct_colour(0.7f, 0.8f, 0.90f, 1.0f),
					vertex_construct_uvcoord(1.1f, 1.2f)
					);

	free(vert);

	Vertex verts[5] = {
		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))},
		{vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))}
	};*/

	Vertex* triangleVertices[3] = {
		{vertex_construct_vertex(vertex_construct_position(-1.0f, -1.0f, -1.0f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.0f, 0.0f, 0.0f, 1.0f), vertex_construct_uvcoord(0.0f, 0.0f))},
		{vertex_construct_vertex(vertex_construct_position(1.0f, -1.0f, -1.0f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.0f, 0.0f, 0.0f, 1.0f), vertex_construct_uvcoord(1.0f, 0.0f))},
		{vertex_construct_vertex(vertex_construct_position(0.0f, 1.0f, -1.0f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.0f, 0.0f, 0.0f, 1.0f), vertex_construct_uvcoord(0.5f, 1.0f))}
	};

	GLuint triangleIndices[3] = { 0, 1, 2 };

	Texture* triangleTextures[2] = { texture_construct_texture("textures/planks.png", "diffuse", 0), texture_construct_texture("textures/planksSpec.png", "specular", 1) };

	/*printf("main: x = %.1f, y = %.1f, z = %.1f\n", triangleVertices[0]->position->x, triangleVertices[0]->position->y, triangleVertices[0]->position->z);
	printf("main: x = %.1f, y = %.1f, z = %.1f\n", triangleVertices[1]->position->x, triangleVertices[1]->position->y, triangleVertices[1]->position->z);
	printf("main: x = %.1f, y = %.1f, z = %.1f\n", triangleVertices[2]->position->x, triangleVertices[2]->position->y, triangleVertices[2]->position->z);*/

	Mesh* triangleMesh = mesh_construct_mesh(triangleVertices, 3, triangleIndices, 3, triangleTextures, 2);

	//VAO* vao = vao_construct_vao();
	//VAO* vao2 = vao_construct_vao();

	//mesh_cleanup(triangleMesh);
	// having these causes errors?
	//free(triangleMesh);
	//free(triangleVertices);
	//free(triangleTextures);
	//free(triangleIndices);

	Shader* basicShader = shader_construct_shader_program("shaders/basic");

	bool gameplayLoop = true;

	while (gameplayLoop)
	{
		glfwSwapBuffers(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
		glfwPollEvents();
		//updates
		//render
		render(basicShader->programID, triangleMesh, 3);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	//free(triangleMesh);

	return 0;
}