#ifndef	TEXTUREFILE_HPP
#define TEXTUREFILE_HPP
#pragma once

#include "Texture.hpp"

enum TextureType {
	Texture_DIFFUSE,
	Texture_SPECULAR,
	Texture_NORMAL,
	Texture_HEIGHT,
	Texture_EMISSIVE,
	Texture_AMBIENT,
	Texture_ICON
};

class TextureFile : public Texture {
	private:
		std::string m_Filepath;
		TextureType m_Type;
	public:
		TextureFile(const std::string& filepath, const TextureType& type, const bool& flipUV = false, const bool& srgb = true);

		// Attacher la texture
		// -------------------
		void Bind() override;

		// Detacher la texture
		// -------------------
		void Unbind() override;

		inline const TextureType getTextureType() { return(this->m_Type); }
		inline const std::string getTexturePath() { return(this->m_Filepath); }
};
#endif