#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "../Scene/Scene.hpp"
#include "OpenGL/Buffer/Framebuffer/HDRFBO.hpp"
#include "../Manager/SceneManager.hpp"

class RenderWindow {
	private:
		// Singleton
		// ---------
		static RenderWindow* m_instance;
		RenderWindow(const bool& fullscreen);
		~RenderWindow();

		// Donnees
		// -------
		unsigned int m_Width;
		unsigned int m_Height;
		GLFWwindow* m_Window = NULL;

		// Framebuffer HDR
		std::shared_ptr<HDRFBO> m_HDRFBO;

		// Pointeur vers le SceneManager
		SceneManager* m_sceneManagerPtr;
	public:
		static RenderWindow* getInstance(const bool& fullscreen = false);

		void Clear();
		void Draw(const float& deltatime, const float& lastframe);
		bool Run();
		void Close();
		void Update();

		GLFWwindow* getWindow() { return this->m_Window; }
};
#endif