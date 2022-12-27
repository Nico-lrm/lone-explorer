#include "Skybox.hpp"

Skybox::Skybox(const std::string& name, const std::vector<std::string>& skyboxFiles, const bool& srgb)
{
    // Dessin d'un cube
    std::vector<float> cubemapVertices
    {         
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    // Preparation des donnees pour le dessin de la skybox
    m_VAO.Bind();
    m_VBO.BindData(cubemapVertices);

    m_VAO.linkAttribute(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    m_VAO.Unbind();
    m_VBO.Unbind();

    // Ajout du shader pour les skybox
    const std::string shaderName{ "skybox" };
    const std::string shaderVert{ "skybox.vert.shader" };
    const std::string shaderFrag{ "skybox.frag.shader" };

    ShaderManager* shaderManager{ ShaderManager::getInstance() };
    this->m_ShaderPtr = shaderManager->createShader(shaderName, shaderVert, shaderFrag);

    // Generer la texture pour la skybox
    const std::string finalName{ std::string(name + "Texture") };

    TextureManager* textureManager = TextureManager::getInstance();
    this->m_TexturePtr = textureManager->createTextureCubemap(finalName, skyboxFiles, srgb);
}

void Skybox::Draw(glm::mat4 camMatrix, glm::vec3 camPos)
{
    // On fait en sorte que la skybox soit derriere tout les elements
    glDepthFunc(GL_LEQUAL);

    // On prépare le modele du cubemap
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, camPos);

    // Lock des weak_ptr
    auto shader = this->m_ShaderPtr.lock();
    auto texture = this->m_TexturePtr.lock();

    // Bind de la texture sur le port 0
    glActiveTexture(GL_TEXTURE0);

    // Uniforms
    shader->Bind();
    shader->setInt("skybox", 0);
    shader->setMat4("camMatrix", camMatrix);
    shader->setMat4("model", model);

    // Dessin
    this->m_VAO.Bind();
    texture->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // On unbind le tout pour eviter tout probleme
    this->m_VAO.Unbind();
    texture->Unbind();
    shader->Unbind();

    // On remet correctement la gestion de la profondeur (les elements les plus proches devant)
    glDepthFunc(GL_LESS);
}