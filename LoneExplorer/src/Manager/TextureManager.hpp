#ifndef	TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP
#pragma once

#include "../Renderer/OpenGL/Texture/TextureBlank.hpp"
#include "../Renderer/OpenGL/Texture/TextureFile.hpp"
#include "../Renderer/OpenGL/Texture/TextureCubemap.hpp"
#include "../Renderer/OpenGL/Texture/TextureCubemapDepth.hpp"
#include "../Renderer/OpenGL/Texture/TextureDepth.hpp"
#include "../Renderer/OpenGL/Texture/TextureFloatBlank.hpp"
#include "Manager.hpp"

class TextureManager : public Manager<Texture> {
	private:
		// Singleton
		static TextureManager* m_instance;
		static std::mutex m_mutex;
		TextureManager() {};
	public:
		// Singleton
		static TextureManager* getInstance();
		std::weak_ptr<TextureBlank> createTextureBlank(const std::string& name, const unsigned int& width, const unsigned int& height);
		std::weak_ptr<TextureFile> createTextureFile(const std::string& name, const std::string& filepath, const TextureType& type, const bool& flipUV = false, const bool& srgb = true);
		std::weak_ptr<TextureCubemap> createTextureCubemap(const std::string& name, const std::vector<std::string>& filepaths, const bool& srgb);
		std::weak_ptr<TextureCubemapDepth> createTextureCubemapDepth(const std::string& name, const unsigned int& resolution);
		std::weak_ptr<TextureDepth> createTextureDepth(const std::string& name, const unsigned int& resolution);
		std::weak_ptr<TextureFloatBlank> createTextureFloatBlank(const std::string& name, const unsigned int& width, const unsigned int& height);
};
#endif