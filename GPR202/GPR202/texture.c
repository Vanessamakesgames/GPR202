#include "texture.h"

#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdbool.h>

Texture* texture_construct_texture(const char* _texturePath, const char* _textureType, GLuint _slot)
{
	Texture* texture = (Texture*)malloc(sizeof(Texture));
	texture->type = _textureType;

	int textureWidth, textureHeight, numberOfColourChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(_texturePath, &textureWidth, &textureHeight, &numberOfColourChannels, 0);

	glGenTextures(1, &texture->ID);
	glActiveTexture(GL_TEXTURE0 + _slot);
	texture->slot = _slot;
	glBindTexture(GL_TEXTURE_2D, texture->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (numberOfColourChannels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	else if (numberOfColourChannels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	else if (numberOfColourChannels == 1) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	else printf("Automatic texture type recognition failed :: %s", _texturePath);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}