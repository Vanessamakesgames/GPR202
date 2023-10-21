#include <stdio.h>
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
//#include <time.h>
#include <stdbool.h>
//#include <cglm/include/cglm/cglm.h>
//#include <string.h>
//#include <stdlib.h>
#include "mesh.h"
//#include <stdlib.h>
#include "shader.h"
#include "gameloop.h"

/* 
A1 requirements:
- 5 primitives
- Primitives coloured with interpolated colors (no distinguishable lines between colours or triangles used to draw mesh)
- matrices used for each mesh
	- translation
	- rotation
	- scale
- camera matrix provided to each mesh (view matrix)
- video demonstrating primitives and explaining code as if assignment marker is a recruiter
	- 2-4 minutes
*/



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

	// right angle triangle
	Vertex rightAngleTriangleVert1 = { .position = {-0.5, 0.5, 1.0}, . colour = {1.0, 0.0, 0.0, 1.0} };
	Vertex rightAngleTriangleVert2 = { .position = {-0.5, -0.5, 1.0}, . colour = {0.0, 1.0, 0.0, 1.0} };
	Vertex rightAngleTriangleVert3 = { .position = {0.5, -0.5, 1.0}, . colour = {0.0, 0.0, 1.0, 1.0} };
	Vertex rightAngleTriangleVerts[3] = { rightAngleTriangleVert1, rightAngleTriangleVert2, rightAngleTriangleVert3};
	GLuint rightAngleTriangleIndices[3] = { 0, 1, 2 };
	Mesh* rightAngleTriangle = mesh_construct_mesh(rightAngleTriangleVerts, 3, rightAngleTriangleIndices, 3);

	vec3 rat_translation = { -0.5, 0.5, 0.0 };
	mesh_translate(rightAngleTriangle, rat_translation);
	vec3 rat_scale = { 0.25, 0.25, 1 };
	mesh_scale(rightAngleTriangle, rat_scale);

	// isosceles triangle
	Vertex isoscelesTriangleVert1 = { .position = {0.0, 1.0, 1.0}, . colour = {1.0, 0.0, 0.0, 1.0} };
	Vertex isoscelesTriangleVert2 = { .position = {-0.5, -1.0, 1.0}, . colour = {0.0, 1.0, 0.0, 1.0} };
	Vertex isoscelesTriangleVert3 = { .position = {0.5, -1.0, 1.0}, . colour = {0.0, 0.0, 1.0, 1.0} };
	Vertex isoscelesTriangleVerts[3] = { isoscelesTriangleVert1, isoscelesTriangleVert2, isoscelesTriangleVert3 };
	GLuint isoscelesTriangleIndices[3] = { 0, 1, 2 };
	Mesh* isoscelesTriangle = mesh_construct_mesh(isoscelesTriangleVerts, 3, isoscelesTriangleIndices, 3);

	vec3 it_translation = { -0.8, -0.5, 0.0 };
	mesh_translate(isoscelesTriangle, it_translation);
	vec3 it_scale = { 0.25, 0.25, 1 };
	mesh_scale(isoscelesTriangle, it_scale);

	// square
	Vertex squareVert1 = { .position = {-0.5, 0.5, 1.0}, . colour = {1.0, 0.0, 0.0, 1.0} };
	Vertex squareVert2 = { .position = {-0.5, -0.5, 1.0}, . colour = {0.0, 1.0, 0.0, 1.0} };
	Vertex squareVert3 = { .position = {0.5, -0.5, 1.0}, . colour = {0.0, 0.0, 1.0, 1.0} };
	Vertex squareVert4 = { .position = {0.5, 0.5, 1.0}, . colour = {0.0, 1.0, 0.0, 1.0} };
	Vertex squareVerts[4] = { squareVert1, squareVert2, squareVert3, squareVert4 };
	GLuint squareIndices[6] = { 0, 1, 3, 1, 2, 3 }; 
	Mesh* square = mesh_construct_mesh(squareVerts, 4, squareIndices, 6);

	vec3 s_translation = { 0.5, 0.5, 0.0 };
	mesh_translate(square, s_translation);
	vec3 s_scale = { 0.25, 0.25, 1 };
	mesh_scale(square, s_scale);

	// hexagon
	Vertex hexagonVert1 = { .position = {-0.125, 0.25, 1.0}, . colour = {1.0, 0.0, 0.0, 1.0} };
	Vertex hexagonVert2 = { .position = {-0.25, 0.0, 1.0}, . colour = {0.0, 1.0, 0.0, 1.0} };
	Vertex hexagonVert3 = { .position = {-0.125, -0.25, 1.0}, . colour = {0.0, 0.0, 1.0, 1.0} };
	Vertex hexagonVert4 = { .position = {0.125, -0.25, 1.0}, . colour = {1.0, 1.0, 0.0, 1.0} };
	Vertex hexagonVert5 = { .position = {0.25, 0.0, 1.0}, . colour = {0.0, 1.0, 1.0, 1.0} };
	Vertex hexagonVert6 = { .position = {0.125, 0.25, 1.0}, . colour = {1.0, 0.0, 1.0, 1.0} };
	Vertex hexagonVerts[6] = { hexagonVert1, hexagonVert2, hexagonVert3, hexagonVert4, hexagonVert5, hexagonVert6 };
	GLuint hexagonIndices[12] = { 0, 1, 5, 1, 4, 5, 1, 3, 4, 1, 2, 3 };
	Mesh* hexagon = mesh_construct_mesh(hexagonVerts, 6, hexagonIndices, 12);

	vec3 h_translation = { 0.8, -0.5, 0.0 };
	mesh_translate(hexagon, h_translation);
	vec3 h_scale = { 0.25, 0.25, 1 };
	mesh_scale(hexagon, h_scale);

	// circle
	Mesh* circle = mesh_construct_circle_mesh(0.75f, 50);

	vec3 c_translation = { 0.0, -0.5, 0.0 };
	mesh_translate(circle, c_translation);
	vec3 c_scale = { 0.25, 0.25, 1 };
	mesh_scale(circle, c_scale);

	Shader* shader = shader_construct_shader_program("shaders/simple");

	mat4 viewMatrix;
	vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
	vec3 cameraDirection = { 0.0f, 0.0f, -1.0f };
	vec3 cameraUp = { 0.0f, 1.0f, 0.0f };
	glm_mat4_identity(viewMatrix);
	glm_look(cameraPosition, cameraDirection, cameraUp, viewMatrix);

	

	bool gameplayLoop = true;
	
		while (gameplayLoop)
		{
			glfwSwapBuffers(window);
			glClearColor(1.0f, 1.0f, 0.9f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
			glfwPollEvents();

			gameloop_update_mesh(shader->programID, rightAngleTriangle, viewMatrix);
			gameloop_render_mesh(shader->programID, rightAngleTriangle);

			gameloop_update_mesh(shader->programID, isoscelesTriangle, viewMatrix);
			gameloop_render_mesh(shader->programID, isoscelesTriangle);

			gameloop_update_mesh(shader->programID, square, viewMatrix);
			gameloop_render_mesh(shader->programID, square);

			gameloop_update_mesh(shader->programID, hexagon, viewMatrix);
			gameloop_render_mesh(shader->programID, hexagon);

			gameloop_update_mesh(shader->programID, circle, viewMatrix);			
			gameloop_render_mesh(shader->programID, circle);

			mesh_unbind_vao();
			shader_deactivate_shader_program();
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