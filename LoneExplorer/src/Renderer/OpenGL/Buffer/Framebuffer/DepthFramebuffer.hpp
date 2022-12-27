#ifndef DEPTHFRAMEBUFFER_HPP
#define DEPTHFRAMEBUFFER_HPP
#pragma once

#include "FBO.hpp"
#include "../../../../Manager/TextureManager.hpp"

class DepthFramebuffer : public FBO
{
	private:
		std::weak_ptr<TextureCubemapDepth> m_TexturePtr;
		static unsigned _CountDFBO;
	public:
		DepthFramebuffer(const unsigned int& resolution);
		std::weak_ptr<TextureCubemapDepth> getTexture() { return this->m_TexturePtr; }
};

#endif