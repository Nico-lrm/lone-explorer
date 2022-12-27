#include "Celestial.hpp"

Celestial::Celestial(const std::weak_ptr<Model> modelPtr, const std::weak_ptr<Shader> shaderPtr, const float mass, const float diameter, const std::weak_ptr<Celestial> celestialPtr, const glm::vec3 position, std::weak_ptr<Light> lightSource) : Entity(modelPtr, shaderPtr, position)
{
	this->m_CelestialPtr = celestialPtr;
	this->m_LightSource = lightSource;
	this->m_Diameter = diameter;
	this->m_Mass = mass;
	m_Position.x *= ECHELLE;

	if (!m_CelestialPtr.expired())
	{
		auto celestialRef{ m_CelestialPtr.lock() };
		if (celestialRef->m_Velocity.z == 0.f)
		{
			this->m_Velocity.z = std::sqrt((float)GRAV_CONST * celestialRef->m_Mass / glm::distance(this->m_Position, celestialRef->m_Position));
		}
		else
		{
			this->m_Velocity.z = std::sqrt((float)GRAV_CONST * celestialRef->m_Mass / glm::distance(this->m_Position, celestialRef->m_Position));
			auto ref = celestialRef->getRef().lock();
			this->m_Velocity.z += std::sqrt((float)GRAV_CONST * ref->m_Mass / glm::distance(this->m_Position, ref->m_Position));
		}
	}
	if (!lightSource.expired())
	{
		auto light = lightSource.lock();
		light->setPosition(m_Position);
	}
}

void Celestial::Draw(std::shared_ptr<Shader> shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPos, const float& deltatime, const float& lastframe, const std::vector<std::shared_ptr<Light>>& lightArray)
{
	auto celestial{ m_CelestialPtr.lock() };
	auto model{ m_ModelPtr.lock() };
	auto shaderPtr{ m_ShaderPtr.lock() };

	// On calcule les premieres transformations du modele
	glm::mat4 modelMatrice = glm::mat4(1.0f);

	// Translation
	if (celestial != nullptr)
		modelMatrice = glm::translate(modelMatrice, celestial->m_Position);
	modelMatrice = glm::translate(modelMatrice, this->m_Position);

	// Scale entier du modele
	if (celestial != nullptr) {
		modelMatrice = glm::scale(modelMatrice, glm::vec3((m_Diameter / celestial->m_Diameter) * 2 * ECHELLE));
	}
	else
	{
		modelMatrice = glm::scale(modelMatrice, glm::vec3(0.25f * ECHELLE / 2));
	}

	// On envoie le tout au modele
	model->Draw(shader, modelMatrice, viewProjMatrix, cameraPos, lightArray);
}

// Test pour la velocite qui depend que de l'astre de ref
void Celestial::updateVelocity(const std::unordered_map<std::string, std::shared_ptr<Celestial>>& celestialMap, const float& deltaTime)
{
	// On initialise un total des forces gravitationnelle qui jouent sur le deplacement de notre objet a 0;
	glm::vec3 totalForceGravitationnelle = glm::vec3(0.0f, 0.0f, 0.0f);

	// On ajoute la force d'attraction de chaque astre sur celui selectionne
	for (auto it = celestialMap.begin(); it != celestialMap.end(); it++)
	{
		//Sinon, on continue notre programme en initialisant un pointeur sur notre autre element
		std::shared_ptr<Celestial> otherCelestialItem{ it->second };

		if (this->m_Position == otherCelestialItem->m_Position) continue;

		// On calcule ensuite la force gravitationnelle de notre element grace a la loi de Newton -> G * (m(objet1)*m(objet2) / d^2)
		float force = (float)GRAV_CONST * this->m_Mass * otherCelestialItem->m_Mass / (float)std::pow(glm::distance(this->m_Position, otherCelestialItem->m_Position), 2);

		// On calcule egalement la direction de notre force en normalisant la valeur de objet2.position - objet1.position
		glm::vec3 forceDirection = glm::normalize(otherCelestialItem->m_Position - this->m_Position);

		// Enfin, on met a jour le total de force en ajoutant la multiplication entre la force gravitationnelle et sa direction
		totalForceGravitationnelle += forceDirection * force;
	}

	// Maintenant, on peut mettre a jour la velocite de notre astre (multiplie par le dt pour eviter toute acceleration entre les differentes config)
	this->m_Velocity += totalForceGravitationnelle / this->m_Mass * deltaTime;
}

void Celestial::updateVelocity(const float& deltaTime)
{
	// On initialise un total des forces gravitationnelle qui jouent sur le deplacement de notre objet a 0;
	glm::vec3 totalForceGravitationnelle = glm::vec3(0.0f, 0.0f, 0.0f);

	if (!m_CelestialPtr.expired())
	{
		auto celestial = m_CelestialPtr.lock();
		// On calcule ensuite la force gravitationnelle de notre element grace a la loi de Newton -> G * (m(objet1)*m(objet2) / d^2)
		float force = (float)GRAV_CONST * this->m_Mass * celestial->m_Mass / (float)std::pow(glm::distance(this->m_Position, celestial->m_Position), 2);

		// On calcule egalement la direction de notre force en normalisant la valeur de objet2.position - objet1.position
		glm::vec3 forceDirection = glm::normalize(celestial->m_Position - this->m_Position);

		// Enfin, on met a jour le total de force en ajoutant la multiplication entre la force gravitationnelle et sa direction
		totalForceGravitationnelle += forceDirection * force;

		// Maintenant, on peut mettre a jour la velocite de notre astre (multiplie par le dt pour eviter toute acceleration entre les differentes config)
		this->m_Velocity += totalForceGravitationnelle / this->m_Mass * deltaTime;
	}
}

void Celestial::updatePosition(const float& deltaTime)
{
	this->m_Position += m_Velocity * deltaTime;

	if (!m_LightSource.expired())
	{
		auto light{ m_LightSource.lock() };
		if (m_Position != light->getPosition())
		{
			light->setPosition(m_Position);
		}
	}
}