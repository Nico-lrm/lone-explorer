#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "../../Renderer/Model/Model.hpp"
#include "../../Renderer/OpenGL/Shader/Shader.hpp"
#include "../../Settings.hpp"

class Entity {
	public:
		virtual void updatePosition(const float& deltaTime) = 0;
		virtual void Draw(std::shared_ptr<Shader> shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPos, const float& deltatime, const float& lastframe, const std::vector<std::shared_ptr<Light>>& lightArray = std::vector<std::shared_ptr<Light>>()) = 0;

		const glm::vec3 getPosition() { return this->m_Position; }
		const glm::vec3 getVelocity() { return this->m_Velocity; }
		std::weak_ptr<Shader> getShaderPtr() { return this->m_ShaderPtr; }
		std::weak_ptr<Model> getModelPtr() { return this->m_ModelPtr; }

	protected:
		std::weak_ptr<Model> m_ModelPtr;
		std::weak_ptr<Shader> m_ShaderPtr;
		glm::vec3 m_Position;
		glm::vec3 m_Velocity = glm::vec3(0.f);

		Entity(const std::weak_ptr<Model>& modelPtr, const std::weak_ptr<Shader>& shaderPtr, const glm::vec3& position) {
			this->m_Position = position;
			this->m_ModelPtr = modelPtr;
			this->m_ShaderPtr = shaderPtr;

			if (modelPtr.expired() || shaderPtr.expired())
				throw std::runtime_error("Test");
		};
};

#endif