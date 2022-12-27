#include "TextureManager.hpp"

TextureManager* TextureManager::m_instance{ nullptr };
std::mutex TextureManager::m_mutex;


TextureManager* TextureManager::getInstance()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (TextureManager::m_instance == nullptr)
    {
        TextureManager::m_instance = new TextureManager();
    }
    return TextureManager::m_instance;
}

std::weak_ptr<TextureBlank> TextureManager::createTextureBlank(const std::string& name, const unsigned int& width, const unsigned int& height)
{
    auto texturePtr{ getElementByName<TextureBlank>(name) };
    if (texturePtr.expired())
    {
        auto newTexture{ std::make_shared<TextureBlank>(width, height) };
        this->m_elementMap.insert(std::make_pair(name, newTexture));
        return std::weak_ptr<TextureBlank>(newTexture);
    }
    else
    {
        std::cout << "L'element \"" << name << "\" existe deja." << std::endl;
    }
    return std::weak_ptr<TextureBlank>(texturePtr);
}

std::weak_ptr<TextureFile> TextureManager::createTextureFile(const std::string& name, const std::string& filepath, const TextureType& type, const bool& flipUV, const bool& srgb)
{
    auto texturePtr{ getElementByName<TextureFile>(name) };
    if (texturePtr.expired())
    {
        auto newTexture{ std::make_shared<TextureFile>(filepath, type, flipUV, srgb) };
        this->m_elementMap.insert(std::make_pair(name, newTexture));

        return std::weak_ptr<TextureFile>(newTexture);
    }
    else
    {
        std::cout << "L'element \"" << name << "\" existe deja." << std::endl;
    }
    return std::weak_ptr<TextureFile>(texturePtr);
}

std::weak_ptr<TextureCubemap> TextureManager::createTextureCubemap(const std::string& name, const std::vector<std::string>& filepaths, const bool& srgb)
{
    auto texturePtr{ getElementByName<TextureCubemap>(name) };
    if (texturePtr.expired())
    {
        auto newTexture{ std::make_shared<TextureCubemap>(filepaths, srgb) };
        this->m_elementMap.insert(std::make_pair(name, newTexture));
        return std::weak_ptr<TextureCubemap>(newTexture);
    }
    else
    {
        std::cout << "L'element \"" << name << "\" existe deja." << std::endl;
    }
    return std::weak_ptr<TextureCubemap>(texturePtr);
}

std::weak_ptr<TextureCubemapDepth> TextureManager::createTextureCubemapDepth(const std::string& name, const unsigned int& resolution)
{
    auto texturePtr{ getElementByName<TextureCubemapDepth>(name) };
    if (texturePtr.expired())
    {
        auto newTexture{ std::make_shared<TextureCubemapDepth>(resolution) };
        this->m_elementMap.insert(std::make_pair(name, newTexture));
        return std::weak_ptr<TextureCubemapDepth>(newTexture);
    }
    else
    {
        std::cout << "L'element \"" << name << "\" existe deja." << std::endl;
    }
    return std::weak_ptr<TextureCubemapDepth>(texturePtr);
}

std::weak_ptr<TextureDepth> TextureManager::createTextureDepth(const std::string& name, const unsigned int& resolution)
{
    return std::weak_ptr<TextureDepth>();
}

std::weak_ptr<TextureFloatBlank> TextureManager::createTextureFloatBlank(const std::string& name, const unsigned int& width, const unsigned int& height)
{
    auto texturePtr{ getElementByName<TextureFloatBlank>(name) };
    if (texturePtr.expired())
    {
        auto newTexture{ std::make_shared<TextureFloatBlank>(width, height) };
        this->m_elementMap.insert(std::make_pair(name, newTexture));
        return std::weak_ptr<TextureFloatBlank>(newTexture);
    }
    else
    {
        std::cout << "L'element \"" << name << "\" existe deja." << std::endl;
    }
    return std::weak_ptr<TextureFloatBlank>(texturePtr);
}
