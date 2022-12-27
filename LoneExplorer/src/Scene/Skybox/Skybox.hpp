#ifndef SKYBOX_HPP
#define	SKYBOX_HPP

#include <glm/glm.hpp>

#include "../../Renderer/OpenGL/Buffer/VAO.hpp"
#include "../../Renderer/OpenGL/Buffer/VBO.hpp"
#include "../../Manager/TextureManager.hpp"
#include "../../Manager/ShaderManager.hpp"

class Skybox {
	private:
		VAO m_VAO;
		VBO m_VBO;
		std::weak_ptr<TextureCubemap> m_TexturePtr;
		std::weak_ptr<Shader> m_ShaderPtr;
	public:
		Skybox(const std::string& name, const std::vector<std::string>& skyboxFiles, const bool& srgb);
		void Draw(glm::mat4 camMatrix, glm::vec3 camPos);
};

#endif