#ifndef	TEXTUREFLOATBLANK_HPP
#define TEXTUREFLOATBLANK_HPP
#pragma once

#include "Texture.hpp"

class TextureFloatBlank : public Texture {
public:
	// Initialise un objet de classe TextureBlank et cree la texture
	// -------------------------------------------------------------
	TextureFloatBlank(const unsigned int& width, const unsigned int& height);

	// Attacher la texture
	// -------------------
	void Bind() override;

	// Detacher la texture
	// -------------------
	void Unbind() override;
};
#endif