#ifndef TEXTUREDEPTH_HPP
#define TEXTUREDEPTH_HPP
#pragma once

#include "Texture.hpp"

class TextureDepth : public Texture {
	private:
		unsigned int m_Resolution;
	public:
		TextureDepth(const unsigned int resolution);

		// Attacher la texture
		// -------------------
		void Bind() override;

		// Detacher la texture
		// -------------------
		void Unbind() override;
};

#endif