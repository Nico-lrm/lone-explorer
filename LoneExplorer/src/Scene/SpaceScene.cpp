#include "SpaceScene.hpp"

void SpaceScene::DrawShadow(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe)
{
    glm::vec3 camPos = m_ActiveCamera->getPosition();
    glm::mat4 camMatrix = m_ActiveCamera->getCameraMatrix(width, height);

    glViewport(0, 0, SHADOW_RES, SHADOW_RES);
    for (auto light : m_LightArray)
    {
        auto depthShader{ light->getDepthFramebufferShader().lock() };
        light->prepareShadow();
        for (auto celestial : m_CelestialMap)
        {
            if(celestial.second->getPosition() != light->getPosition())
                celestial.second->Draw(depthShader, camMatrix, camPos, deltatime, lastframe);
        }
        light->releaseShadow();
    }
    glViewport(0, 0, width, height);
}

void SpaceScene::DrawComplete(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe)
{
    glm::vec3 camPos = m_ActiveCamera->getPosition();
    glm::mat4 camMatrix = m_ActiveCamera->getCameraMatrix(width, height);

    for (auto celestial : m_CelestialMap)
    {
        auto shader{ celestial.second->getShaderPtr().lock() };
        shader->Bind();

        for (auto light : m_LightArray)
        {
            light->applyLight(shader);
        }
        shader->setFloat("time", lastframe);
        shader->setInt("numberPointLight", PointLight::getNumberPointLight());
        #ifdef SHADOW_ENABLE
                shader->setInt("shadow_enable", 1);
        #else
                shader->setInt("shadow_enable", 0);
        #endif // SHADOW_ENABLE
        celestial.second->Draw(shader, camMatrix, camPos, deltatime, lastframe, m_LightArray);

        shader->Unbind();
    }

    for (auto asteroid : m_AsteroidMap)
    {
        auto shader{ asteroid.second->getShaderPtr().lock() };
        shader->Bind();

        for (auto light : m_LightArray)
        {
            light->applyLight(shader);
        }
        shader->setInt("numberPointLight", PointLight::getNumberPointLight());
        #ifdef SHADOW_ENABLE
            shader->setInt("shadow_enable", 1);
        #else
            shader->setInt("shadow_enable", 0);
        #endif // SHADOW_ENABLE
        asteroid.second->Draw(shader, camMatrix, camPos, deltatime, lastframe, m_LightArray);
        shader->Unbind();
    }

    m_OrbitsPtr->Draw(camMatrix);
    m_ActiveSkybox->Draw(camMatrix, camPos);

    #ifdef SHADOW_ENABLE
        DrawShadow(width, height, deltatime, lastframe);
    #endif // SHADOW_ENABLE
}

void SpaceScene::Update(const float& deltaTime)
{
    for (auto celestial : m_CelestialMap)
    {
        celestial.second->updateVelocity(m_CelestialMap, deltaTime);
        celestial.second->updatePosition(deltaTime);
    }
    #ifdef SHADOW_ENABLE
        for (auto light : m_LightArray)
        {
            light->Update();
        }
    #endif // SHADOW_ENABLE
}

std::weak_ptr<Celestial> SpaceScene::addCelestial(const std::string& name, const std::weak_ptr<Model>& modelPtr, const std::weak_ptr<Shader>& shaderPtr, const float& mass, const float& diameter, const std::weak_ptr<Celestial>& celestialPtr, const glm::vec3& position, std::weak_ptr<Light> lightPtr)
{
    auto celestial{ getCelestial(name) };
    if (celestial.expired())
    {
        std::shared_ptr<Celestial> newCelestial{ nullptr };
        try
        {
            newCelestial = std::make_shared<Celestial>(modelPtr, shaderPtr, mass, diameter, celestialPtr, position, lightPtr);
            this->m_CelestialMap.insert(std::make_pair(name, newCelestial));
            m_OrbitsPtr->addNewOrbit(celestialPtr, position.x * ECHELLE);
            //std::cout << "Ajout de " << name << std::endl;
            return std::weak_ptr<Celestial>(newCelestial);
        }
        catch (std::runtime_error& e)
        {
            std::cerr << "Celestial : " <<  e.what() << std::endl;
            //abort();
        }

    }
    return celestial;
}

std::weak_ptr<Celestial> SpaceScene::getCelestial(const std::string& name)
{
    // On verifie si l'iterateur trouve bien l'element
    auto it{ this->m_CelestialMap.find(name) };

    // Si le shader n'est pas trouve dans la map
    if (it == m_CelestialMap.end())
        return std::weak_ptr<Celestial>();

    // Sinon, on renvoie un observer de celui-ci
    return it->second;
}

std::weak_ptr<Asteroid> SpaceScene::addAsteroid(const std::string& name, const float& radius, const float& offset, const unsigned int& count, const std::weak_ptr<Celestial>& celestialPtr, const std::weak_ptr<Shader>& shaderPtr, const std::weak_ptr<Model>& modelPtr, const double& scaleFact)
{
    auto asteroid{ getAsteroid(name) };
    if (asteroid.expired())
    {
        std::shared_ptr<Asteroid> newAsteroid{ nullptr };
        try
        {
            newAsteroid = std::make_shared<Asteroid>(radius, offset, count, celestialPtr, shaderPtr, modelPtr, scaleFact);
            this->m_AsteroidMap.insert(std::make_pair(name, newAsteroid));
            return std::weak_ptr<Asteroid>(newAsteroid);
        }
        catch (std::runtime_error& e)
        {
            std::cerr << "Asteroid : " << e.what() << std::endl;
            //abort();
        }

    }
    return asteroid;
}

std::weak_ptr<Asteroid> SpaceScene::getAsteroid(const std::string& name)
{
    // On verifie si l'iterateur trouve bien l'element
    auto it{ this->m_AsteroidMap.find(name) };

    // Si le shader n'est pas trouve dans la map
    if (it == m_AsteroidMap.end())
        return std::weak_ptr<Asteroid>();

    // Sinon, on renvoie un observer de celui-ci
    return it->second;
}