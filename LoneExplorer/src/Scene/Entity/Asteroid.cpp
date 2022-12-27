#include "Asteroid.hpp"

std::mutex mut;

Asteroid::Asteroid(const float radius, const float offset, const unsigned int count,  const std::weak_ptr<Celestial> celestialPtr, const std::weak_ptr<Shader> shaderPtr, const std::weak_ptr<Model> modelPtr, const double scaleFact) : Entity(modelPtr, shaderPtr, glm::vec3(0.0f))
{
	this->m_CelestialPtr = celestialPtr;
	this->m_Count = count;
	this->m_Radius = radius * ECHELLE;
	this->m_Offset = offset;

    auto shader{ shaderPtr.lock() };

    auto celestial{ celestialPtr.lock() };
    this->m_Position = celestial->getPosition();

    for (unsigned int i = 0; i < count; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, this->m_Position);

        float angle = (float)i / (float)count * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.1f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>(((rand() % 3) / scaleFact));
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));


        // 4. now add to list of matrices
        m_Models.push_back(model);
    }

    m_ModelSSBO.AttachData(m_Models);
}

void Asteroid::Draw(std::shared_ptr<Shader> shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPos, const float& deltatime, const float& lastframe, const std::vector<std::shared_ptr<Light>>& lightArray)
{
    auto model{ m_ModelPtr.lock() };

    // On connecte à chaque fois les SSBO aux ports 0 & 1 du shader "asteroid"
    m_ModelSSBO.connect(shader, 0, "bufferModelMatrices");

    model->DrawInstanced(shader, viewProjMatrix, cameraPos, m_Count, lightArray);
}

void Asteroid::updatePosition(const float& deltaTime)
{
    auto celestial{ m_CelestialPtr.lock() };
    this->m_Position = celestial->getPosition();
}

void Asteroid::updateModels()
{
    for (unsigned int i = 0; i < m_Count; i++)
    {
        this->m_Models[i] = glm::mat4(1.0);
        this->m_Models[i] = glm::translate(this->m_Models[i], m_Position);

        float angle = (float)i / (float)m_Count * 360.0f;
        float displacement = (rand() % (int)(2 * m_Offset * 100)) / 100.0f - m_Offset;
        float x = sin(angle) * m_Radius + displacement;
        displacement = (rand() % (int)(2 * m_Offset * 100)) / 100.0f - m_Offset;
        float y = displacement * 0.3f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * m_Offset * 100)) / 100.0f - m_Offset;
        float z = cos(angle) * m_Radius + displacement;
        this->m_Models[i] = glm::translate(this->m_Models[i], glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 3) / 1500.0 + 0.000335);
        this->m_Models[i] = glm::scale(this->m_Models[i], glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        this->m_Models[i] = glm::rotate(this->m_Models[i], rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
    }
}

void Asteroid::updateSSBO()
{
    updateModels();
    m_ModelSSBO.updateData(m_Models);
}