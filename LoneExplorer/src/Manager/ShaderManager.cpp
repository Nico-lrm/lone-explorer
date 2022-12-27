#include "ShaderManager.hpp"

// Initialisation variable static
ShaderManager* ShaderManager::m_instance = nullptr;
std::mutex ShaderManager::m_mutex;


// R�cup�rer le singleton de la classe
ShaderManager* ShaderManager::getInstance()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (ShaderManager::m_instance == nullptr)
    {
        ShaderManager::m_instance = new ShaderManager();
    }
    return ShaderManager::m_instance;
}

std::weak_ptr<Shader> ShaderManager::createShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
    auto shaderPtr{ getElementByName(name) };
    std::string ressourceFolder{ "../Ressources/shader/" };
    if (shaderPtr.expired())
    {
        std::shared_ptr<Shader> newShader{ nullptr };
        if (geometryPath == "")
        {
            newShader = std::make_shared<Shader>(ressourceFolder + vertexPath, ressourceFolder + fragmentPath);
        }
        else
        {
            newShader = std::make_shared<Shader>(ressourceFolder + vertexPath, ressourceFolder + fragmentPath, ressourceFolder + geometryPath);
        }
        this->m_elementMap.insert(std::make_pair(name, newShader));

        return std::weak_ptr<Shader>(newShader);
    }
    else
    {
        std::cout << "L'element \"" << name << "\" existe deja." << std::endl;
    }
    return shaderPtr;
}