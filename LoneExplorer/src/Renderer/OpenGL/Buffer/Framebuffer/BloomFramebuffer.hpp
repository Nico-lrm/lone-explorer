#ifndef BLOOMFRAMEBUFFER_HPP
#define BLOOMFRAMEBUFFER_HPP
#pragma once

#include "../VAO.hpp"
#include "FBO.hpp"
#include "../../../../Manager/ShaderManager.hpp"
#include "../../../../Manager/TextureManager.hpp"

class BloomFramebuffer
{
	private:
		FBO m_Framebuffers[2];
		std::weak_ptr<TextureFloatBlank> m_arrayTexturePtr[2];
		std::weak_ptr<Shader> m_blurShaderPtr;

		bool m_horizontal = true;
		unsigned int m_amount = 10;
	public:
		BloomFramebuffer(const unsigned int& width, const unsigned int& height);
		void Blur(VAO& refVAO, std::weak_ptr<TextureFloatBlank>& brightTex);

		inline std::weak_ptr<TextureFloatBlank> getDrawingTexture() { return this->m_arrayTexturePtr[!m_horizontal]; }
};

#endif