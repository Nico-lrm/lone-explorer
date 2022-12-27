#ifndef VBO_HPP
#define VBO_HPP
#pragma once

#include "../OpenGLObject.hpp"

#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

class VBO : public OpenGLObject
{
	public:
        // Constructeur - Genere le buffer
        // -------------------------------
		VBO();

        // Attacher le buffer et lui passer les vertex
        // -------------------------------------------
		void BindData(std::vector<Vertex>& vertices);
        void BindData(std::vector<float>& vertices);

        // Attacher le buffer (il faut que les donnees soit saisies au moins une fois)
        // ---------------------------------------------------------------------------
		void Bind() override;

        // Detacher le buffer
        // ------------------
		void Unbind() override;

        // Supprimer le buffer
        // -------------------
		void Delete() override;
};
#endif