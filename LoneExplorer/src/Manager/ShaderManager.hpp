#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP
#pragma once

#include "Manager.hpp"
#include "../Renderer/OpenGL/Shader/Shader.hpp"

class ShaderManager : public Manager<Shader> {
	private:
		static ShaderManager* m_instance;
		static std::mutex m_mutex;
		ShaderManager() {};
	public:
		static ShaderManager* getInstance();
		std::weak_ptr<Shader> createShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
};
#endif