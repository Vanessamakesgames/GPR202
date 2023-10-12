#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew/glew.h>

typedef struct Texture
{
	GLuint ID;
	const char* type;
	GLuint slot;
} Texture;

#endif
