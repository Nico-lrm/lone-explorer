#ifndef MULTISAMPLEFRAMEBUFFER_HPP
#define MULTISAMPLEFRAMEBUFFER_HPP
#pragma once

#include "FBO.hpp"
#include "../RBO.hpp"
#include "../../../../Manager/TextureManager.hpp"

class MultisampleFramebuffer : public FBO
{
	private:
		RBO m_RBO;
	public:
		MultisampleFramebuffer(const unsigned int& sample, const unsigned int& width, const unsigned int& height);
		void Blit(FBO& otherFramebuffer);
};

#endif