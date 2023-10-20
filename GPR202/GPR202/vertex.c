//#include "vertex.h"
//
//#include <stdlib.h>
//
//#include <stdio.h>
//
//Vertex* vertex_construct_vertex(Position _position, Normal _normal, Colour _colour, UVCoord _uvcoord)
//{
//	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
//	//vertex->position = NULL;
//
//	vertex->position = (Position*)malloc(sizeof(Position));
//	if (vertex->position == NULL) printf("vertex->position == NULL\n");
//	vertex->position = &_position;
//	printf("vertex_construct_vertex: vertex->position: x = %.1f, y = %.1f, z = %.1f\n", vertex->position->x, vertex->position->y, vertex->position->z);
//	printf("vertex_construct_vertex: _position: x = %.1f, y = %.1f, z = %.1f\n", _position.x, _position.y, _position.z);
//	vertex->normal = (Normal*)malloc(sizeof(Normal));
//	if (vertex->normal == NULL) printf("vertex->normal == NULL\n");
//	vertex->normal = &_normal;
//	vertex->colour = (Colour*)malloc(sizeof(Colour));
//	if (vertex->colour == NULL) printf("vertex->colour == NULL\n");
//	vertex->colour = &_colour;
//	vertex->uvcoord = (UVCoord*)malloc(sizeof(UVCoord));
//	if (vertex->uvcoord == NULL) printf("vertex->uvcoord == NULL\n");
//	vertex->uvcoord = &_uvcoord;
//
//	return vertex;
//}
//
//Position vertex_construct_position(GLfloat _positionX, GLfloat _positionY, GLfloat _positionZ)
//{
//	Position position;
//	position.x = _positionX;
//	position.y = _positionY;
//	position.z = _positionZ;
//
//	printf("vertex_construct_position: x = % .1f, y = %.1f, z = %.1f\n", position.x, position.y, position.z);
//
//	return position;
//}
//
//Normal vertex_construct_normal(GLfloat _normalX, GLfloat _normalY, GLfloat _normalZ)
//{
//	Normal normal;
//	normal.x = _normalX;
//	normal.y = _normalY;
//	normal.z = _normalZ;
//
//	return normal;
//}
//
//Colour vertex_construct_colour(GLfloat _colourR, GLfloat _colourG, GLfloat _colourB, GLfloat _colourA)
//{
//	Colour colour;
//	colour.r = _colourR;
//	colour.g = _colourG;
//	colour.b = _colourB;
//	colour.a = _colourA;
//
//	return colour;
//}
//
//UVCoord vertex_construct_uvcoord(GLfloat _uvcoordU, GLfloat _uvcoordV)
//{
//	UVCoord uvcoord;
//	uvcoord.u = _uvcoordU;
//	uvcoord.v = _uvcoordV;
//
//	return uvcoord;
//}
