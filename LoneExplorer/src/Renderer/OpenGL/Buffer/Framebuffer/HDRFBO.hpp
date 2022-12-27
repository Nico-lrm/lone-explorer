#ifndef HDRFBO_HPP 
#define HDRFBO_HPP
#pragma once

#include "BloomFramebuffer.hpp"
#include "../VBO.hpp"
#include "../RBO.hpp"
#include "../../../../Manager/SceneManager.hpp"

class HDRFBO : public FBO {
	protected:
		std::weak_ptr<TextureFloatBlank> m_mainTexturePtr;
		std::weak_ptr<TextureFloatBlank> m_brightTexturePtr;
		std::weak_ptr<Shader> m_shaderPtr;
		std::weak_ptr<Shader> m_shaderBlurPtr;
		std::unique_ptr<RBO> m_depthRBO;

		// Forme du dessin
		VAO m_VAO;
		VBO m_VBO;

		// Valeur d'exposition
		float m_exposure = EXPOSURE;

		// Bloom
		std::unique_ptr<BloomFramebuffer> m_BloomFramebuffer;
	public:
		HDRFBO(const unsigned int& width, const unsigned int& height);
		void Draw();
		void Blur();
};
#endif