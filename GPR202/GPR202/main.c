#include <stdio.h>
#define GLEW_STATIC
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <time.h>
#include <stdbool.h>
#include "mesh.h"
#include <stdlib.h>

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
	glFrontFace(GL_CCW);
	
	// 3D stuff
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	//Vertex vertices[] = {};

	//Mesh* firstMesh = mesh_construct_mesh()

	//Vertex* v = vertex_construct_vertex(vertex_construct_position(1.0f, 1.0f, 1.0f), vertex_construct_normal(1.0f, 1.0f, 1.0f), vertex_construct_colour(1.0f, 1.0f, 1.0f, 1.0f), vertex_construct_uvcoord(1.0f, 1.0f));

	Vertex* vert = vertex_construct_vertex(
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
	};

	// does not work
	/*Vertex* pVerts = (Vertex*)malloc(sizeof(Vertex) * 5);
	pVerts = (Vertex){
		vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f)),
		vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f)),
		vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f)),
		vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f)),
		vertex_construct_vertex(vertex_construct_position(0.1f, 0.2f, 0.3f), vertex_construct_normal(0.1f, 0.2f, 0.3f), vertex_construct_colour(0.1f, 0.2f, 0.3f, 0.4f), vertex_construct_uvcoord(0.1f, 0.2f))
	};*/

	GLuint inds = { 0 };

	Mesh* mesh = mesh_construct_mesh(verts, 5, inds, 1);

	bool gameplayLoop = true;

	while (gameplayLoop)
	{
		glfwSwapBuffers(window);
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
		glfwPollEvents();
		//updates
		//render
		glBindVertexArray(0);
		glUseProgram(0);
	}

	return 0;
}