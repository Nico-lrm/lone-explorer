#ifndef	LIGHT_HPP
#define LIGHT_HPP
#pragma once

#include "../../Manager/ShaderManager.hpp"
#include "../../Renderer/OpenGL/Buffer/Framebuffer/DepthFramebuffer.hpp"
#include "../../Settings.hpp"

class Light {
	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;

		// Gestion des ombres
		std::shared_ptr<DepthFramebuffer> m_DepthFBO;
		std::weak_ptr<Shader> m_DepthShader;
		std::vector<glm::mat4> m_ShadowTransforms;

		// Redefinir les matrices du DFBO pour les ombres
		void setShadowMatrices()
		{
			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_RES / (float)SHADOW_RES, 1.f, FAR);
			m_ShadowTransforms.push_back(shadowProj * glm::lookAt(m_Position, m_Position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			m_ShadowTransforms.push_back(shadowProj * glm::lookAt(m_Position, m_Position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			m_ShadowTransforms.push_back(shadowProj * glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			m_ShadowTransforms.push_back(shadowProj * glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
			m_ShadowTransforms.push_back(shadowProj * glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
			m_ShadowTransforms.push_back(shadowProj * glm::lookAt(m_Position, m_Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		}

		Light(const glm::vec3& position = glm::vec3(0.f), const glm::vec3& ambient = glm::vec3(0.025f), const glm::vec3& diffuse = glm::vec3(1.0f), const glm::vec3& specular = glm::vec3(0.25f))
		{
			this->m_Position = position;
			this->m_Ambient = ambient;
			this->m_Diffuse = diffuse;
			this->m_Specular = specular;

			// Creation du DFBO pour les ombres lies a cette lumiere
			#ifdef SHADOW_ENABLE
				m_DepthFBO = std::make_shared<DepthFramebuffer>(SHADOW_RES);
				auto shadMan = ShaderManager::getInstance();
				m_DepthShader = shadMan->createShader("depthShader", "depthshadow.vert.shader", "depthshadow.frag.shader", "depthshadow.geom.shader");
			#endif // SHADOW_ENABLE
		};

	public:
		virtual void applyLight(const std::shared_ptr<Shader>& shaderPtr) = 0;
		virtual void Update() = 0;
		virtual void prepareShadow() = 0;
		virtual void releaseShadow() = 0;

		std::weak_ptr<Shader> getDepthFramebufferShader() { return m_DepthShader; }
		std::weak_ptr<DepthFramebuffer> getDepthFramebuffer() { return m_DepthFBO; }

		void setPosition(const glm::vec3& newPos) { this->m_Position = newPos; }
		const glm::vec3& getPosition() { return std::ref(m_Position); }

};
#endif