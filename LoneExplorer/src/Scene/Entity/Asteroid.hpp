#ifndef ASTEROID_HPP
#define	ASTEROID_HPP
#pragma once

#include "Celestial.hpp"
#include "../../Renderer/OpenGL/Buffer/SSBO.hpp"

#include <thread>
#include <mutex>

class Asteroid : public Entity
{
private:
	std::vector<glm::mat4> m_Models;
	std::vector<glm::mat3> m_Normals;
	std::weak_ptr<Celestial> m_CelestialPtr;
	float m_Radius;
	float m_Offset;
	unsigned int m_Count;
	SSBO m_ModelSSBO;
public:
	Asteroid(const float radius, const float offset, const unsigned int count, const std::weak_ptr<Celestial> celestialPtr, const std::weak_ptr<Shader> shaderPtr, const std::weak_ptr<Model> modelPtr, const double scaleFact = 25.0);
	~Asteroid() {};
	void Draw(std::shared_ptr<Shader> shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPos, const float& deltatime, const float& lastframe, const std::vector<std::shared_ptr<Light>>& lightArray = std::vector<std::shared_ptr<Light>>()) override;
	void updatePosition(const float& deltaTime) override;
	void updateModels( );
	void updateSSBO();
};

#endif