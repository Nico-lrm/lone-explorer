#include "ColorFramebuffer.hpp"

unsigned int ColorFramebuffer::_CountCFBO = 0;

ColorFramebuffer::ColorFramebuffer(const unsigned int& width, const unsigned int& height)
{
	// Recuperer le textureManager
	auto textureManager{ TextureManager::getInstance() };
	m_TexturePtr = textureManager->createTextureBlank("colorFramebuffer" + std::to_string(ColorFramebuffer::_CountCFBO++), width, height);

	// Utiliser la texture fraichement creee
	auto texture{ m_TexturePtr.lock() };

	this->Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->getID(), 0);
	this->Unbind();
}