#ifndef	TEXTUREBLANK_HPP
#define TEXTUREBLANK_HPP
#pragma once

#include "Texture.hpp"

class TextureBlank : public Texture {
	public:
		// Initialise un objet de classe TextureBlank et cree la texture
		// -------------------------------------------------------------
		TextureBlank(const unsigned int& width, const unsigned int& height);

		// Attacher la texture
		// -------------------
		void Bind() override;

		// Detacher la texture
		// -------------------
		void Unbind() override;
};
#endif