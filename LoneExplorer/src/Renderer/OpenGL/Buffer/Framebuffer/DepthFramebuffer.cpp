#include "DepthFramebuffer.hpp"

unsigned DepthFramebuffer::_CountDFBO{ 0 };

DepthFramebuffer::DepthFramebuffer(const unsigned int& resolution)
{
	// Recuperer le textureManager
	auto textureManager{ TextureManager::getInstance() };
	m_TexturePtr = textureManager->createTextureCubemapDepth("depthCubemap" + std::to_string(DepthFramebuffer::_CountDFBO++), resolution);

	// Utiliser la texture fraichement creee
	auto textureCubemapPtr{ m_TexturePtr.lock() };

	this->Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureCubemapPtr->getID(), 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	this->Unbind();
}
