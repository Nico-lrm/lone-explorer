#ifndef APPLICATION_HPP
#define	APPLICATION_HPP
#pragma once

#include "Manager/ModelManager.hpp"
#include "Manager/ShaderManager.hpp"
#include "Manager/SceneManager.hpp"
#include "Manager/TextureManager.hpp"

#include "Renderer/RenderWindow.hpp"

#include <chrono>

class Application {
	private:
		// Singleton
		// ---------
		static Application* m_instance;
		Application(const bool& fullscreen);

		ModelManager* m_ModelManager{ nullptr };
		ShaderManager* m_ShaderManager{ nullptr };
		SceneManager* m_SceneManager{ nullptr };
		TextureManager* m_TextureManager{ nullptr };
		RenderWindow* m_RenderWindow{ nullptr };

		unsigned int m_Width;
		unsigned int m_Height;

		// Gestion du temps
		float m_lastFrame{ 0.0f };
		float m_deltaTime{ 0.0f };
		float m_currentFrame{ 0.f };
		unsigned int m_countFrame{ 0 };

		// Pour fonction de callback
		static bool m_firstMouse;
		static float m_lastX;
		static float m_lastY;

		void UpdateTime();
		void Inputs();

		// Initialiser les donnees de maniere fixe
		void InitSpaceRenderer();

	public:
		// Singleton
		static Application* getInstance(const bool& fullscreen = false);

		// Fonction de callback
		static void mouse_camera_callback(GLFWwindow* window, double xposIn, double yposIn);

		// Lancer la boucle de l'application
		void Run();
};

#endif