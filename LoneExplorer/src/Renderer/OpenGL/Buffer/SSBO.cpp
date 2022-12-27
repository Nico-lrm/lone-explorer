#include "SSBO.hpp"

unsigned int SSBO::m_NextSlot{ 0 };

SSBO::SSBO()
{
	glGenBuffers(1, &m_ID);
}

void SSBO::AttachData(std::vector<glm::mat4>& models)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, models.size() * sizeof(glm::mat4), models.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::AttachData(std::vector<glm::mat3>& models)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ID);
	glBufferData(GL_SHADER_STORAGE_BUFFER, models.size() * sizeof(glm::mat3), models.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::Bind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ID);
}

void SSBO::Unbind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::Delete()
{
	glDeleteBuffers(1, &this->m_ID);
}

void SSBO::updateData(std::vector<glm::mat4>& models)
{
	this->Bind();
	GLvoid* pointer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
	memcpy(pointer, models.data(), models.size() * sizeof(glm::mat4));
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	this->Unbind();
}

void SSBO::updateData(std::vector<glm::mat3>& models)
{
	this->Bind();
	GLvoid* pointer = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
	memcpy(pointer, models.data(), models.size() * sizeof(glm::mat3));
	glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	this->Unbind();
}

void SSBO::connect(std::shared_ptr<Shader> shaderPtr, GLuint index, const char* name)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ID);
	GLuint block_index = 0;
	block_index = glGetProgramResourceIndex(shaderPtr->getID(), GL_SHADER_STORAGE_BLOCK, name);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, this->m_ID);

	// Optionnel
	glShaderStorageBlockBinding(shaderPtr->getID(), block_index, index);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
