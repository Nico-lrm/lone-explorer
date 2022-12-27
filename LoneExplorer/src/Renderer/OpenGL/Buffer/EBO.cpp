#include "EBO.hpp"

EBO::EBO()
{
	glGenBuffers(1, &m_ID);
}

void EBO::BindData(std::vector<GLuint>& indices)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &m_ID);
}