//#include "vao.h"
//
//#include <stdlib.h>
//#include <stdio.h>
//
//VAO vao_construct_vao()
//{
//	VAO vao;
//	glGenVertexArrays(1, &vao.ID);
//	printf("ID of vao is : %d\n", vao.ID);
//	return vao;
//}
//
//void vao_link_attributes(VBO _vbo, GLuint _layout, GLuint _numberOfComponents, GLenum _type, GLsizeiptr _stride, void* _offset)
//{
//	glBindBuffer(GL_ARRAY_BUFFER, _vbo.ID);
//	glVertexAttribPointer(_layout, _numberOfComponents, _type, GL_FALSE, _stride, _offset);
//	glEnableVertexAttribArray(_layout);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//void vao_bind(GLuint _vaoID)
//{
//	glBindVertexArray(_vaoID);
//}
//
//void vao_unbind()
//{
//	glBindVertexArray(0);
//}
//
//void vao_delete(VAO* vao)
//{
//	glDeleteVertexArrays(1, vao->ID);
//}