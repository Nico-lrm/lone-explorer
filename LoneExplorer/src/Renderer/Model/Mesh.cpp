#include "Mesh.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<std::weak_ptr<TextureFile>>& textures, const float& opacity)
{
    this->m_vertices = vertices;
    this->m_indices = indices;
    this->m_textures = textures;
    this->m_opacity = opacity;

    // Une fois que les donnees sont stockes dans le maillage, on peut initialiser les elements pour le rendu
    setupMesh();
}

void Mesh::Draw()
{
    // On dessine la maille
    m_VAO.Bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLuint>(m_indices.size()), GL_UNSIGNED_INT, 0);
    m_VAO.Unbind();
}

void Mesh::DrawInstanced(const unsigned int& count)
{
    // On dessine la maille
    m_VAO.Bind();
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLuint>(m_indices.size()), GL_UNSIGNED_INT, 0, count);
    m_VAO.Unbind();
}

void Mesh::prepareMesh(std::shared_ptr<Shader>& shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPosition, const std::vector<std::shared_ptr<Light>>& lightArray)
{
    // Attacher la bonne texture au shader
    unsigned int diffuseNr{ 1 };
    unsigned int specularNr{ 1 };
    unsigned int normalNr{ 1 };
    unsigned int heightNr{ 1 };
    unsigned int emissiveNr{ 1 };
    unsigned int baseColorNr{ 1 };
    unsigned int ambientNr{ 1 };

    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        auto texture{ m_textures[i].lock() };
        // On active le textureUnit avant d'attacher notre texture
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name;
        TextureType texType{ texture->getTextureType() };

        switch (texType)
        {
        case Texture_DIFFUSE:
            name = "texture_diffuse";
            number = std::to_string(diffuseNr++);
            break;
        case Texture_SPECULAR:
            name = "texture_specular";
            number = std::to_string(specularNr++);
            break;
        case Texture_NORMAL:
            name = "texture_normal";
            number = std::to_string(normalNr++);
            break;
        case Texture_HEIGHT:
            name = "texture_height";
            number = std::to_string(heightNr++);
            break;
        case Texture_EMISSIVE:
            name = "texture_emissive";
            number = std::to_string(emissiveNr++);
            break;
        case Texture_AMBIENT:
            name = "texture_ambient";
            number = std::to_string(ambientNr++);
            break;
        }

        // On applique maintenant l'uniform de la texture (type + nombre) et on l'envoie sur le bon textureUnit
        shader->setInt(std::string("material." + name + number), i);
        //std::cout << std::string("material." + name + number) << std::endl;
        // Enfin, on attache notre texture une fois que tout est active.
        texture->Bind();
    }
    // Matrices pour la camera
    shader->setMat4("viewProjMatrix", viewProjMatrix);
    
    shader->setVec3("cameraPos", cameraPosition);

    // Reflection de la lumiere de la maille & opacite
    shader->setFloat("material.opacity", m_opacity);
    shader->setFloat("material.shininess", 64);

    // Dessiner les depthsMap pour les ombres si le vector de light est passe en params
    #ifdef SHADOW_ENABLE
        if (lightArray.size() > 0)
        {
            size_t nbTexture = m_textures.size();
            for (size_t i = 0; i < lightArray.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + nbTexture + i);
                lightArray[i]->getDepthFramebuffer().lock()->getTexture().lock()->Bind();
                shader->setInt("depthMap[" + std::to_string(i) + "]", nbTexture + i);
            }
            shader->setFloat("far_plane", FAR);
        }
    #endif // SHADOW_ENABLE
}


void Mesh::releaseMesh(std::shared_ptr<Shader>& shader)
{
    // On unbind l'ensemble des textures utilisees
    for (unsigned int i = 0; i < m_textures.size(); i++)
    {
        auto texture{ m_textures[i].lock() };
        texture->Unbind();
    }

    // On reinitialise les textures du maillage pour la prochaine maille - TEMPORAIRE, C'EST PAS LEGAL DE FAIRE CA
    glUniform1i(glGetUniformLocation(shader->getID(), "material.texture_diffuse1"), 16);
    glUniform1i(glGetUniformLocation(shader->getID(), "material.texture_specular1"), 16);
    glUniform1i(glGetUniformLocation(shader->getID(), "material.texture_normal1"), 16);
    glUniform1i(glGetUniformLocation(shader->getID(), "material.texture_height1"), 16);
    glUniform1i(glGetUniformLocation(shader->getID(), "material.texture_emissive1"), 16);
    glUniform1i(glGetUniformLocation(shader->getID(), "material.texture_basecolor1"), 16);
    glUniform1i(glGetUniformLocation(shader->getID(), "material.texture_ambient1"), 16);

    // On remet la texture active a 0
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::applyMeshTransformation(std::shared_ptr<Shader>& shader, const glm::mat4& model)
{
    // Appliquer les dernieres transformations liees a la maille ainsi que les valeurs pour la matrice normale, et la camera
    glm::mat4 modelLastTransform = model * m_transform;
    shader->setMat4("model", modelLastTransform);
}

void Mesh::setupMesh()
{
    m_VAO.Bind();

    // Charger les donnees dans le VBO & l'EBO
    m_VBO.BindData(this->m_vertices);
    m_EBO.BindData(this->m_indices);

    // Passer les donnees au layout
    m_VAO.linkAttribute(0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    m_VAO.linkAttribute(1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Normal));
    m_VAO.linkAttribute(2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::TexCoords));
    m_VAO.linkAttribute(3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Tangent));
    m_VAO.linkAttribute(4, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Bitangent));

    //On unbind notre VAO par securite
    m_VAO.Unbind();
    m_VBO.Unbind();
    m_EBO.Unbind();
}