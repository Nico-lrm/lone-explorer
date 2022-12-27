#ifndef MODEL_HPP
#define MODEL_HPP
#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../Manager/TextureManager.hpp"
#include "Mesh.hpp"

class Model
{
    public:
        // Constructeur - Necessite le chemin et une valeur vrai/faux pour savoir s'il faut retourner la texture
        // -----------------------------------------------------------------------------------------------------
        Model(Assimp::Importer& importer, const std::string& path, const bool& flipTexture);

        // Dessiner le modele, c-a-d l'ensemble de ses mailles
        // ---------------------------------------------------
        void Draw(std::shared_ptr<Shader>& shader, const glm::mat4& model, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPosition, const std::vector<std::shared_ptr<Light>>& lightArray = std::vector<std::shared_ptr<Light>>());
        void DrawInstanced(std::shared_ptr<Shader>& shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPosition, const unsigned int& count, const std::vector<std::shared_ptr<Light>>& lightArray = std::vector<std::shared_ptr<Light>>());

    private:
        // Donnees du modele
        // -----------------
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        std::string m_path;

        // A retirer a l'avenir
        bool m_flipTexture;

        // Charger le modèle 3D à l'aide d'Assimp
        // --------------------------------------
        void loadModel(Assimp::Importer& importer, std::string const& path);

        // Recupere sur chaque noeud l'ensemble des mailles - recursive
        // ------------------------------------------------------------
        void processNode(aiNode* node, const aiScene* scene, glm::mat4 parent_transform);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        // Charge l'ensemble des materiaux et textures de l'objet
        // ------------------------------------------------------
        void loadMaterialTextures(const aiScene* scene, aiMaterial* mat, aiTextureType type, std::vector<std::weak_ptr<TextureFile>>& texturesVector, std::vector<std::weak_ptr<TextureFile>>& textureLoaded);

        // Convertir les mat4 de Assimp vers GLM
        // -------------------------------------
        glm::mat4 AiMatrix4x4ToGlm(const aiMatrix4x4* from);
};
#endif