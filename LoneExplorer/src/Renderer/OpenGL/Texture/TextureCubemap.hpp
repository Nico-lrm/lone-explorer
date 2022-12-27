#ifndef	TEXTURESKYBOX_HPP
#define TEXTURESKYBOX_HPP
#pragma once

#include "Texture.hpp"

class TextureCubemap : public Texture {
	private:
		std::vector<std::string> m_Filepaths;
	public:
		TextureCubemap(const std::vector<std::string>& filepaths, const bool& srgb);
		void Bind() override;
		void Unbind() override;
		std::vector<std::string> getFiles() { return this->m_Filepaths; }
};
#endif