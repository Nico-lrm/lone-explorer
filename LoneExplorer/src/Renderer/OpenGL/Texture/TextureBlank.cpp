#include "TextureBlank.hpp"

TextureBlank::TextureBlank(const unsigned int& width, const unsigned int& height)
{
	glBindTexture(GL_TEXTURE_2D, this->m_ID);

	// On genere une texture sans donnees de la taille de notre fenetre
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	// Parametres de la texture du FBO
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBlank::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->m_ID);
}

void TextureBlank::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}