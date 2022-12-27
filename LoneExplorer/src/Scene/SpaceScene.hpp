#ifndef SPACESCENE_HPP
#define SPACESCENE_HPP
#pragma once

#include "Scene.hpp"
#include "Entity/Celestial.hpp"
#include "Entity/Asteroid.hpp"
#include "Orbits.hpp"

class SpaceScene : public Scene {
private:
	std::unordered_map<std::string, std::shared_ptr<Celestial>> m_CelestialMap;
	std::unordered_map<std::string, std::shared_ptr<Asteroid>> m_AsteroidMap;
	std::unique_ptr<Orbits> m_OrbitsPtr;

public:
	SpaceScene() {
		// Initialiser les lignes d'orbites
		m_OrbitsPtr = std::make_unique<Orbits>();
	}

	void DrawShadow(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe) override;
	void DrawComplete(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe) override;
	void Update(const float& deltaTime) override;

	std::weak_ptr<Celestial> addCelestial(const std::string& name, const std::weak_ptr<Model>& modelPtr, const std::weak_ptr<Shader>& shaderPtr, const float& mass, const float& diameter, const std::weak_ptr<Celestial>& celestialPtr = std::weak_ptr<Celestial>(), const glm::vec3& position = glm::vec3(0.0f), std::weak_ptr<Light> lightPtr = std::weak_ptr<Light>());
	std::weak_ptr<Celestial> getCelestial(const std::string& name);

	std::weak_ptr<Asteroid> addAsteroid(const std::string& name, const float& radius, const float& offset, const unsigned int& count, const std::weak_ptr<Celestial>& celestialPtr, const std::weak_ptr<Shader>& shaderPtr, const std::weak_ptr<Model>& modelPtr, const double& scaleFact = 25.0);
	std::weak_ptr<Asteroid> getAsteroid(const std::string& name);
};

#endif