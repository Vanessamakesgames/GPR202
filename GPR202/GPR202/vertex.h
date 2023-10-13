#ifndef VERTEX_H
#define VERTEX_H

#define GLEW_STATIC
#include <glew.h>

typedef struct Position
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Position;

typedef struct Normal
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Normal;

typedef struct Colour
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
} Colour;

typedef struct UVCoord
{
	GLfloat u; // horizontal axis
	GLfloat v; // vertical axis
	// 0, 0 is bottom left -- 1, 1 is top right
} UVCoord;

typedef struct Vertex
{
	Position* position;
	Normal* normal;
	Colour* colour;
	UVCoord* uvcoord;
} Vertex;

Vertex* vertex_construct_vertex(Position _position, Normal _normal, Colour _colour, UVCoord _uvcoord);
Position vertex_construct_position(GLfloat _positionX, GLfloat _positionY, GLfloat _positionZ);
Normal vertex_construct_normal(GLfloat _normalX, GLfloat _normalY, GLfloat _normalZ);
Colour vertex_construct_colour(GLfloat _colourR, GLfloat _colourG, GLfloat _colourB, GLfloat _colourA);
UVCoord vertex_construct_uvcoord(GLfloat _uvcoordU, GLfloat _uvcoordV);

#endif