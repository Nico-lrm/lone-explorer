#include "VAO.hpp"

VAO::~VAO()
{
	//glDeleteVertexArrays(1, &this->m_ID);
}

VAO::VAO()
{
	glGenVertexArrays(1, &(this->m_ID));
}

void VAO::linkAttribute(const GLuint layout, const GLint size, const GLenum type, const GLsizei stride, const void* pointer) 
{
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, pointer);
}

void VAO::Bind() 
{
	glBindVertexArray(this->m_ID);
}

void VAO::Unbind() 
{
	glBindVertexArray(0);
}

void VAO::Delete() 
{
	glDeleteVertexArrays(1, &(this->m_ID));
}