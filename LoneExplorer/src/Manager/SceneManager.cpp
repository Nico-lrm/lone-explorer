#include "SceneManager.hpp"

// Initialisation variable static
SceneManager* SceneManager::m_instance = nullptr;
std::mutex SceneManager::m_mutex;

SceneManager* SceneManager::getInstance()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (SceneManager::m_instance == nullptr)
    {
        SceneManager::m_instance = new SceneManager();
    }
    return SceneManager::m_instance;
}

void SceneManager::createScene(const std::string& name)
{
    auto scene{ getElementByName(name) };
    if (scene.expired())
    {
        auto scenePtr{ std::make_shared<SpaceScene>() };
        m_elementMap.insert(std::make_pair(name, scenePtr));

        // S'il n'y a pas de scene active
        if (m_ActiveScene == nullptr)
            m_ActiveScene = scenePtr;
    }
}

void SceneManager::setActiveScene(const std::string& name)
{
    auto scene{ getElementByName(name) };
    if (!scene.expired())
    {
        m_ActiveScene = scene.lock();
    }
}

void SceneManager::addCameraActiveScene(const std::string& name, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->addCamera(name, position, up, yaw, pitch);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}

void SceneManager::addSkyboxActiveScene(const std::string& name, const std::vector<std::string>& skyboxFiles, const bool& srgb)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->addSkybox(name, skyboxFiles, srgb);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}

void SceneManager::setActiveCameraActiveScene(const std::string& name)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->setActiveCamera(name);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}

void SceneManager::setActiveSkyboxActiveScene(const std::string& name)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->setActiveSkybox(name);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}

void SceneManager::updateActiveCameraPositionActiveScene(const CameraDirection& direction, const float& deltaTime)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->updateActiveCameraPosition(direction, deltaTime);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}

void SceneManager::updateActiveCameraOrientationActiveScene(const float& xoffset, const float& yoffset)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->updateActiveCameraOrientation(xoffset, yoffset);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}

void SceneManager::addPointLightActiveScene(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, const float& linear, const float& quadratic)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->addPointLight(position, ambient, diffuse, specular, linear, quadratic);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}

std::weak_ptr<Celestial> SceneManager::addCelestialActiveScene(const std::string& name, const std::weak_ptr<Model>& modelPtr, const std::weak_ptr<Shader>& shaderPtr, const float& mass, const float& diameter, const std::weak_ptr<Celestial>& celestialPtr, const glm::vec3& position, std::weak_ptr<Light> lightPtr)
{
    if (m_ActiveScene != nullptr)
    {
        return m_ActiveScene->addCelestial(name, modelPtr, shaderPtr, mass, diameter, celestialPtr, position, lightPtr);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
    return std::weak_ptr<Celestial>();
}

std::weak_ptr<Celestial> SceneManager::getCelestialActiveScene(const std::string& name)
{
    if (m_ActiveScene != nullptr)
    {
        return m_ActiveScene->getCelestial(name);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
    return std::weak_ptr<Celestial>();
}

std::weak_ptr<Asteroid> SceneManager::addAsteroidActiveScene(const std::string& name, const float& radius, const float& offset, const unsigned int& count, const std::weak_ptr<Celestial>& celestialPtr, const std::weak_ptr<Shader>& shaderPtr, const std::weak_ptr<Model>& modelPtr, const double& scaleFact)
{
    if (m_ActiveScene != nullptr)
    {
        return m_ActiveScene->addAsteroid(name, radius, offset, count, celestialPtr, shaderPtr, modelPtr, scaleFact);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
    return std::weak_ptr<Asteroid>();
}

std::weak_ptr<Asteroid> SceneManager::getAsteroidActiveScene(const std::string& name)
{
    if (m_ActiveScene != nullptr)
    {
        return m_ActiveScene->getAsteroid(name);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
    return std::weak_ptr<Asteroid>();
}

void SceneManager::DrawActiveScene(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe)
{
    if (m_ActiveScene != nullptr)
    {
        m_ActiveScene->Update(deltatime);
        m_ActiveScene->DrawComplete(width, height, deltatime, lastframe);
    }
    else
    {
        std::cout << "Aucune scene active, veuillez en creer au moins une" << std::endl;
    }
}
