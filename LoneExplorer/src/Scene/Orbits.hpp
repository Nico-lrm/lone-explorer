#ifndef ORBITS_HPP
#define ORBITS_HPP
#pragma once

#define M_PI 3.14159265358979323846

#include "../Manager/ShaderManager.hpp"
#include "Entity/Celestial.hpp"

#include <numbers>
#include <vector>

class Orbits {
	private:
		VAO m_VAO;
		VBO m_VBO;
		std::vector<float> m_OrbitVertex;
		std::weak_ptr<Shader> m_LineShader;
		std::vector<std::pair<std::weak_ptr<Celestial>, float>> m_Data;
	public:
		Orbits();
		void Draw(glm::mat4 viewProjMatrix);
		void addNewOrbit(const std::weak_ptr<Celestial>& celestialRef, const float& xCoord);
		void removeOrbit(int id);
		void clearOrbits();
};

#endif