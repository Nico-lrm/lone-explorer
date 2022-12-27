#include "Scene.hpp"

std::shared_ptr<Camera> Scene::getCamera(const std::string& name)
{
    // On verifie si l'iterateur trouve bien l'element
    auto it{ this->m_CameraMap.find(name) };

    // Si le shader n'est pas trouve dans la map
    if (it == m_CameraMap.end())
        return nullptr;

    // Sinon, on renvoie un observer de celui-ci
    return it->second;
}

std::shared_ptr<Skybox> Scene::getSkybox(const std::string& name)
{
    // On verifie si l'iterateur trouve bien l'element
    auto it{ this->m_SkyboxMap.find(name) };

    // Si le shader n'est pas trouve dans la map
    if (it == m_SkyboxMap.end())
        return nullptr;

    // Sinon, on renvoie un observer de celui-ci
    return it->second;
}

void Scene::addCamera(const std::string& name, const glm::vec3& position, const glm::vec3& up, const float& yaw, const float& pitch)
{
    if (getCamera(name) == nullptr)
    {
        auto cameraPtr{ std::make_shared<Camera>(position, up, yaw, pitch) };
        this->m_CameraMap.insert(std::make_pair(name, cameraPtr));

        if (this->m_ActiveCamera == nullptr)
        {
            this->m_ActiveCamera = cameraPtr;
        }
    }
    else
    {
        std::cout << "La camera '" << name << "' existe deja." << std::endl;
    }
}

void Scene::addSkybox(const std::string& name, const std::vector<std::string>& skyboxFiles, const bool& srgb)
{
    if (getSkybox(name) == nullptr)
    {
        auto skyboxPtr{ std::make_shared<Skybox>(name, skyboxFiles, srgb) };
        this->m_SkyboxMap.insert(std::make_pair(name, skyboxPtr));

        if (this->m_ActiveSkybox == nullptr)
        {
            this->m_ActiveSkybox = skyboxPtr;
        }
    }
    else
    {
        std::cout << "La skybox '" << name << "' existe deja." << std::endl;
    }
}

void Scene::setActiveCamera(const std::string& name)
{
    auto cameraPtr{ getCamera(name) };
    if (cameraPtr != nullptr)
    {
        this->m_ActiveCamera = cameraPtr;
    }
    else
    {
        std::cout << "Impossible de trouver la camera '" << name << "'." << std::endl;
    }
}

void Scene::setActiveSkybox(const std::string& name)
{
    auto skyboxPtr{ getSkybox(name) };
    if (skyboxPtr != nullptr)
    {
        this->m_ActiveSkybox = skyboxPtr;
    }
    else
    {
        std::cout << "Impossible de trouver la skybox '" << name << "'." << std::endl;
    }
}

void Scene::updateActiveCameraPosition(const CameraDirection& direction, const float& deltaTime)
{
    m_ActiveCamera->Move(direction, deltaTime);
}

void Scene::updateActiveCameraOrientation(const float& xoffset, const float& yoffset)
{
    m_ActiveCamera->Look(xoffset, yoffset);
}

void Scene::addPointLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const float& linear, const float& quadratic)
{
    m_LightArray.push_back(std::make_shared<PointLight>(position, ambient, diffuse, specular, linear, quadratic));
}
