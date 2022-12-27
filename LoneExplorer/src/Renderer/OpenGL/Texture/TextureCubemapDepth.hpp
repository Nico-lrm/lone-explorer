#ifndef TEXTURECUBEMAPDEPTH_HPP
#define TEXTURECUBEMAPDEPTH_HPP
#pragma once

#include "Texture.hpp"

class TextureCubemapDepth : public Texture
{
	private:
		unsigned int m_Resolution;
	public:
		TextureCubemapDepth(const unsigned int resolution);

		// Attacher la texture
		// -------------------
		void Bind() override;

		// Detacher la texture
		// -------------------
		void Unbind() override;
};

#endif