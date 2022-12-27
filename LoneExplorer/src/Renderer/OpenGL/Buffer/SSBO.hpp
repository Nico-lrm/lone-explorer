#ifndef	SSBO_HPP
#define SSBO_HPP
#pragma once

#include "../Shader/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>

class SSBO : public OpenGLObject {
	private:
		static unsigned int m_NextSlot;

	public:
		SSBO();

		// Attacher le buffer et lui passer les indices
		// --------------------------------------------
		void AttachData(std::vector<glm::mat4>& models);
		void AttachData(std::vector<glm::mat3>& models);

		// Attacher le buffer (il faut que les donnees soit saisies au moins une fois)
		// ---------------------------------------------------------------------------
		void Bind() override;

		// Detacher le buffer
		// ------------------
		void Unbind() override;

		// Supprimer le buffer
		// -------------------
		void Delete() override;

		// Mettre a jour les donnees du buffers pour le rendu instancie
		// ------------------------------------------------------------
		void updateData(std::vector<glm::mat4>& models);
		void updateData(std::vector<glm::mat3>& models);

		// Connecter le SSBO au shader
		// ---------------------------
		void connect(std::shared_ptr<Shader> shaderPtr, GLuint index, const char* name);
};
#endif