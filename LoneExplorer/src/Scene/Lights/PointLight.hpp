#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP
#pragma once

#include "Light.hpp"
#include <memory>

class PointLight : public Light {
	private:
		float m_Constant = 1.0f;
		float m_Linear;
		float m_Quadratic;

		// Tenir le compte de pointLight creees
		static unsigned _NumberPointLight;

		// L'index de l'instance
		unsigned m_IndexPointLight;

	public:
		PointLight(const glm::vec3& position = glm::vec3(0.f), const glm::vec3& ambient = glm::vec3(0.025f), const glm::vec3& diffuse = glm::vec3(1.0f), const glm::vec3& specular = glm::vec3(0.1f), const float& linear = 0.00000068359375f, const float& quadratic = 0.00000000341796875f);
		void applyLight(const std::shared_ptr<Shader>& shaderPtr) override;
		void Update() override;
		void prepareShadow();
		void releaseShadow();
		
		static const unsigned getNumberPointLight() { return PointLight::_NumberPointLight; };
};

#endif