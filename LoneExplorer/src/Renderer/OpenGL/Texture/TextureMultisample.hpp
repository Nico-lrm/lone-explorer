#ifndef	TEXTUREMULTISAMPLE_HPP
#define TEXTUREMULTISAMPLE_HPP
#pragma once

#include "Texture.hpp"

class TextureMultisample : public Texture
{
public:
	TextureMultisample(const unsigned int& sample, const unsigned int& width, const unsigned int& height);
	void Bind() override;
	void Unbind() override;
};

#endif