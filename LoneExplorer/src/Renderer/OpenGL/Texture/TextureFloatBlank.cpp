#include "TextureFloatBlank.hpp"

TextureFloatBlank::TextureFloatBlank(const unsigned int& width, const unsigned int& height)
{
	glBindTexture(GL_TEXTURE_2D, this->m_ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureFloatBlank::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->m_ID);
}

void TextureFloatBlank::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}