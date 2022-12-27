#include "RBO.hpp"

RBO::RBO(const unsigned int& width, const unsigned int& height)
{
	glGenRenderbuffers(1, &(this->m_ID));
	glBindRenderbuffer(GL_RENDERBUFFER, this->m_ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RBO::RBO()
{
	glGenRenderbuffers(1, &(this->m_ID));
}

void RBO::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, this->m_ID);
}

void RBO::Unbind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RBO::Delete()
{
	glDeleteRenderbuffers(1, &m_ID);
}

void RBO::setRenderbufferStorage(const unsigned int& width, const unsigned int& height)
{
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
}

void RBO::setRenderbufferStorageMultisample(const unsigned int& sample, const unsigned int& width, const unsigned int& height)
{
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, sample, GL_DEPTH24_STENCIL8, width, height);
}
