#include "TextureMultisample.hpp"

TextureMultisample::TextureMultisample(const unsigned int& sample, const unsigned int& width, const unsigned int& height)
{
	Bind();
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample, GL_RGB, width, height, GL_TRUE);
	Unbind();
}

void TextureMultisample::Bind()
{
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ID);
}

void TextureMultisample::Unbind()
{
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
}