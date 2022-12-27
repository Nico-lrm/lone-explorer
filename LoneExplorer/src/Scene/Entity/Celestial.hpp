#ifndef CELESTIAL_HPP
#define	CELESTIAL_HPP
#pragma once

#define GRAV_CONST 6.67E-14

#include "Entity.hpp"

class Celestial : public Entity {
	protected:
		std::weak_ptr<Celestial> m_CelestialPtr;
		std::weak_ptr<Light> m_LightSource;
		float m_Mass;
		float m_Diameter;
	public:
		Celestial(const std::weak_ptr<Model> modelPtr, const std::weak_ptr<Shader> shaderPtr, const float mass, const float diameter, const std::weak_ptr<Celestial> celestialPtr = std::weak_ptr<Celestial>(), const glm::vec3 position = glm::vec3(0.0f), std::weak_ptr<Light> lightSource = std::weak_ptr<Light>());
		void Draw(std::shared_ptr<Shader> shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPos, const float& deltatime, const float& lastframe, const std::vector<std::shared_ptr<Light>>& lightArray = std::vector<std::shared_ptr<Light>>()) override;
		void updateVelocity(const std::unordered_map<std::string, std::shared_ptr<Celestial>>& celestialMap, const float& deltaTime);
		void updateVelocity(const float& deltaTime);
		void updatePosition(const float& deltaTime) override;

		std::weak_ptr<Celestial> getRef() { return this->m_CelestialPtr; }
};

#endif