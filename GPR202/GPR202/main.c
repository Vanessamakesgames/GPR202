#include <stdio.h>
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>
#include <stdbool.h>
#include "mesh.h"
#include "shader.h"
#include "gameloop.h"

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
	GLFWwindow* window = glfwCreateWindow(512, 512, "GPR202 A1", NULL, NULL);
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

	// right angle triangle
	Vertex rightAngleTriangleVerts[3] =
	{
		[0].position = {-0.5, 0.5, 1.0},	[0].colour = {1.0, 0.0, 0.0, 1.0},
		[1].position = {-0.5, -0.5, 1.0},	[1].colour = {0.0, 1.0, 0.0, 1.0},
		[2].position = {0.5, -0.5, 1.0},	[2].colour = {0.0, 0.0, 1.0, 1.0}
	};
	GLuint rightAngleTriangleIndices[3] = { 0, 1, 2 };
	Mesh* rightAngleTriangle = mesh_construct_mesh(rightAngleTriangleVerts, 3, rightAngleTriangleIndices, 3);

	vec3 rat_translation = { -0.8, 0.5, 0.0 };
	mesh_translate(rightAngleTriangle, rat_translation);
	vec3 rat_scale = { 0.25, 0.25, 1 };
	mesh_scale(rightAngleTriangle, rat_scale);

	// isosceles triangle
	Vertex isoscelesTriangleVerts[3] =
	{
		[0].position = {0.0, 1.0, 1.0},		[0].colour = {1.0, 0.0, 0.0, 1.0},
		[1].position = {-0.5, -1.0, 1.0},	[1].colour = {0.0, 1.0, 0.0, 1.0},
		[2].position = {0.5, -1.0, 1.0},	[2].colour = {0.0, 0.0, 1.0, 1.0}
	};
	GLuint isoscelesTriangleIndices[3] = { 0, 1, 2 };
	Mesh* isoscelesTriangle = mesh_construct_mesh(isoscelesTriangleVerts, 3, isoscelesTriangleIndices, 3);

	vec3 it_translation = { -0.8, -0.5, 0.0 };
	mesh_translate(isoscelesTriangle, it_translation);
	vec3 it_scale = { 0.25, 0.25, 1 };
	mesh_scale(isoscelesTriangle, it_scale);

	// square
	Vertex squareVerts[4] = 
	{ 
		[0] .position = {-0.5, 0.5, 1.0},	[0].colour = {1.0, 0.0, 0.0, 1.0},
		[1].position = {-0.5, -0.5, 1.0},	[1].colour = {0.0, 1.0, 0.0, 1.0},
		[2].position = {0.5, -0.5, 1.0},	[2].colour = {0.0, 0.0, 1.0, 1.0},
		[3].position = {0.5, 0.5, 1.0},		[3].colour = {0.25, 0.5, 0.75, 1.0} 
	};
	GLuint squareIndices[6] = { 0, 1, 3, 1, 2, 3 }; 
	Mesh* square = mesh_construct_mesh(squareVerts, 4, squareIndices, 6);

	vec3 s_translation = { 0.8, 0.5, 0.0 };
	mesh_translate(square, s_translation);
	vec3 s_scale = { 0.25, 0.25, 1 };
	mesh_scale(square, s_scale);

	// hexagon
	Vertex hexagonVerts[6] = 
	{
		[0].position = {-0.125, 0.25, 1.0},		[0].colour = {1.0, 0.0, 0.0, 1.0},
		[1].position = {-0.25, 0.0, 1.0},		[1].colour = {0.0, 1.0, 0.0, 1.0},
		[2].position = {-0.125, -0.25, 1.0},	[2].colour = {0.0, 0.0, 1.0, 1.0},
		[3].position = {0.125, -0.25, 1.0},		[3].colour = {1.0, 1.0, 0.0, 1.0},
		[4].position = {0.25, 0.0, 1.0},		[4].colour = {0.0, 1.0, 1.0, 1.0},
		[5].position = {0.125, 0.25, 1.0},		[5].colour = {1.0, 0.0, 1.0, 1.0}
	};
	GLuint hexagonIndices[12] = { 0, 1, 5, 1, 4, 5, 1, 3, 4, 1, 2, 3 };
	Mesh* hexagon = mesh_construct_mesh(hexagonVerts, 6, hexagonIndices, 12);

	vec3 h_translation = { 0.8, -0.5, 0.0 };
	mesh_translate(hexagon, h_translation);
	vec3 h_scale = { 0.5, 0.5, 1 };
	mesh_scale(hexagon, h_scale);

	// circle
	Mesh* circle = mesh_construct_circle_mesh(0.75f, 50);

	vec3 c_translation = { 0.0, 0.5, 0.0 };
	mesh_translate(circle, c_translation);
	vec3 c_scale = { 0.25, 0.25, 1 };
	mesh_scale(circle, c_scale);

	// better circle
	Mesh* betterCircle = mesh_construct_better_circle_mesh(0.75f, 50);

	vec3 bc_translation = { 0.0, -0.5, 0.0 };
	mesh_translate(betterCircle, bc_translation);
	vec3 bc_scale = { 0.25, 0.25, 1 };
	mesh_scale(betterCircle, bc_scale);

	Shader* shader = shader_construct_shader_program("shaders/simple");

	// camera matrix stuff
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

			// update uniforms then render each mesh before moving to next mesh
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

			gameloop_update_mesh(shader->programID, betterCircle, viewMatrix);
			gameloop_render_mesh(shader->programID, betterCircle);

			mesh_unbind_vao();
			shader_deactivate_shader_program();

			// user presses escape to close program and free memory
			if (glfwGetKey(window, GLFW_KEY_ESCAPE)) gameplayLoop = false;
		}

		// free allocated memory
		free(rightAngleTriangle);
		free(isoscelesTriangle);
		free(square);
		free(hexagon);
		free(circle);
		free(betterCircle);
		free(shader);
		
		return 0;
}