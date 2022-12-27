#ifndef SCENE_HPP
#define	SCENE_HPP

#pragma once

#include "Camera/Camera.hpp"
#include "Lights/PointLight.hpp"
#include "Skybox/Skybox.hpp"

#include <vector>
#include <unordered_map>

class Scene {
	protected:
		std::vector<std::shared_ptr<Light>> m_LightArray;
		std::unordered_map<std::string, std::shared_ptr<Camera>> m_CameraMap;
		std::unordered_map<std::string, std::shared_ptr<Skybox>> m_SkyboxMap;

		std::shared_ptr<Camera> m_ActiveCamera = nullptr;
		std::shared_ptr<Skybox> m_ActiveSkybox = nullptr;

		std::shared_ptr<Camera> getCamera(const std::string& name);
		std::shared_ptr<Skybox> getSkybox(const std::string& name);
	public:
		Scene() {};

		// A modifie
		virtual void DrawComplete(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe) = 0;
		virtual void DrawShadow(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe) = 0;
		virtual void Update(const float& deltaTime) = 0;

		void addCamera(const std::string& name, const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), const float& yaw = YAW, const float& pitch = PITCH);
		void addSkybox(const std::string& name, const std::vector<std::string>& skyboxFiles, const bool& srgb);

		void setActiveCamera(const std::string& name);
		void setActiveSkybox(const std::string& name);

		void updateActiveCameraPosition(const CameraDirection& direction, const float& deltaTime);
		void updateActiveCameraOrientation(const float& xoffset, const float& yoffset);

		void addPointLight(const glm::vec3& position = glm::vec3(0.f), const glm::vec3& ambient = glm::vec3(1.0f), const glm::vec3& diffuse = glm::vec3(1.0f), const glm::vec3& specular = glm::vec3(0.25f), const float& linear = 0.00000068359375f, const float& quadratic = 0.00000000341796875f);
		std::weak_ptr<Light> getPointLight(unsigned id) { return std::weak_ptr<Light>(m_LightArray[id]); }
};

#endif