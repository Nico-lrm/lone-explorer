#ifndef COLORFRAMEBUFFER_HPP
#define COLORFRAMEBUFFER_HPP
#pragma once

#include "FBO.hpp"
#include "../../../../Manager/TextureManager.hpp"

class ColorFramebuffer : public FBO
{
	private:
		std::weak_ptr<TextureBlank> m_TexturePtr;
		static unsigned int _CountCFBO;
	public:
		ColorFramebuffer(const unsigned int& width, const unsigned int& height);
};

#endif