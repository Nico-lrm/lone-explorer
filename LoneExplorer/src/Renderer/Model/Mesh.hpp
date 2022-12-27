#ifndef MESH_HPP
#define MESH_HPP
#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "../OpenGL/Buffer/VAO.hpp"
#include "../OpenGL/Buffer/VBO.hpp"
#include "../OpenGL/Buffer/EBO.hpp"
#include "../OpenGL/Texture/TextureFile.hpp"
#include "../OpenGL/Shader/Shader.hpp"
#include "../../Scene/Lights/PointLight.hpp"

class Mesh {
    public:
        // Constructeur - Charge les donnees pour les stocker et lance l'initialisation des variables pour rendu
        // -----------------------------------------------------------------------------------------------------
        Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<std::weak_ptr<TextureFile>>& textures, const float& opacity);

        // Dessiner le maillage
        // --------------------
        void Draw();
        void DrawInstanced(const unsigned int& count);

        // Preparer la maille
        // ------------------
        void prepareMesh(std::shared_ptr<Shader>& shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPosition, const std::vector<std::shared_ptr<Light>>& lightArray = std::vector<std::shared_ptr<Light>>());

        // Reinitialiser les ressources pour dessiner une autre maille
        // -----------------------------------------------------------
        void releaseMesh(std::shared_ptr<Shader>& shader);

        // Si dessin non instancie, on applique les transformations
        // --------------------------------------------------------
        void applyMeshTransformation(std::shared_ptr<Shader>& shader, const glm::mat4& model);

        // Getter - Setter
        // ---------------
        void setTransformation(const glm::mat4& transform) { this->m_transform = transform; }
        inline size_t getNumberTexture() { return m_textures.size(); }

    private:
        // Donnees
        // -------
        std::vector<Vertex> m_vertices;
        std::vector<GLuint> m_indices;
        std::vector<std::weak_ptr<TextureFile>> m_textures;

        // Opacite et transformation de la maille
        // --------------------------------------
        float m_opacity;
        glm::mat4 m_transform;

        // Rendu
        // -----
        VAO m_VAO;
        VBO m_VBO;
        EBO m_EBO;

        // Initialiser le maillage avec les donnees
        // ----------------------------------------
        void setupMesh();
};
#endif