#include "VBO.hpp"

VBO::VBO()
{
	glGenBuffers(1, &m_ID);
}

void VBO::BindData(std::vector<Vertex>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::BindData(std::vector<float>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() 
{
	glDeleteBuffers(1, &m_ID);
}