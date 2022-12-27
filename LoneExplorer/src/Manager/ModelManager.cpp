#include "ModelManager.hpp"


// Initialisation variable static
ModelManager* ModelManager::m_instance{ nullptr };
std::mutex ModelManager::m_mutex;

// Recuperer le singleton de la classe
ModelManager* ModelManager::getInstance()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (ModelManager::m_instance == nullptr)
    {
        ModelManager::m_instance = new ModelManager();
    }
    return ModelManager::m_instance;
}

std::weak_ptr<Model> ModelManager::createModel(const std::string& name, const std::string& path, const bool& flipTexture)
{
    auto modelPtr{ getElementByName(name) };
    if (modelPtr.expired())
    {
        std::string ressourceFolder{ "../Ressources/model/" };

        std::shared_ptr<Model> newModel{ std::make_shared<Model>(this->m_Importer, ressourceFolder + path, flipTexture) };

        // Ajouter l'element dans la map
        this->m_elementMap.insert(std::make_pair(name, newModel));

        return std::weak_ptr<Model>(newModel);
    }
    else
    {
        std::cout << "L'element \"" << name << "\" existe deja." << std::endl;
    }
    return modelPtr;
}