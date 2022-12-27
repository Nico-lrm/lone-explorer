#ifndef	SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#pragma once

#include "Manager.hpp"
#include "../Scene/SpaceScene.hpp"

class SceneManager : public Manager<SpaceScene> {
	private:
		// Singleton
		static SceneManager* m_instance;
		static std::mutex m_mutex;
		SceneManager() {};

		std::shared_ptr<SpaceScene> m_ActiveScene;
	public:
		// Singleton
		static SceneManager* getInstance();
		void createScene(const std::string& name);
		void setActiveScene(const std::string& name);

		void addCameraActiveScene(const std::string& name, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		void addSkyboxActiveScene(const std::string& name, const std::vector<std::string>& skyboxFiles, const bool& srgb);

		void setActiveCameraActiveScene(const std::string& name);
		void setActiveSkyboxActiveScene(const std::string& name);

		void updateActiveCameraPositionActiveScene(const CameraDirection& direction, const float& deltaTime);
		void updateActiveCameraOrientationActiveScene(const float& xoffset, const float& yoffset);

		void addPointLightActiveScene(const glm::vec3& position = glm::vec3(0.f), const glm::vec3& ambient = glm::vec3(1.0f), const glm::vec3& diffuse = glm::vec3(1.0f), const glm::vec3& specular = glm::vec3(0.25f), const float& linear = 0.00000068359375f, const float& quadratic = 0.00000000341796875f);
		std::weak_ptr<Light> getPointLightActiveScene(unsigned id) { return m_ActiveScene->getPointLight(id); }

		std::weak_ptr<Celestial> addCelestialActiveScene(const std::string& name, const std::weak_ptr<Model>& modelPtr, const std::weak_ptr<Shader>& shaderPtr, const float& mass, const float& diameter, const std::weak_ptr<Celestial>& celestialPtr = std::weak_ptr<Celestial>(), const glm::vec3& position = glm::vec3(0.0f), std::weak_ptr<Light> lightPtr = std::weak_ptr<Light>());
		std::weak_ptr<Celestial> getCelestialActiveScene(const std::string& name);

		std::weak_ptr<Asteroid> addAsteroidActiveScene(const std::string& name, const float& radius, const float& offset, const unsigned int& count, const std::weak_ptr<Celestial>& celestialPtr, const std::weak_ptr<Shader>& shaderPtr, const std::weak_ptr<Model>& modelPtr, const double& scaleFact = 25.0);
		std::weak_ptr<Asteroid> getAsteroidActiveScene(const std::string& name);

		void DrawActiveScene(const unsigned int& width, const unsigned int& height, const float& deltatime, const float& lastframe);
};
#endif