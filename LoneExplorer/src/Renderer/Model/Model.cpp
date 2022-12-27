#include "Model.hpp"

Model::Model(Assimp::Importer& importer, const std::string& path, const bool& flipTexture) : m_flipTexture(flipTexture)
{
    std::cout << "Chargement du modele 3D : " << path << std::endl;
    loadModel(importer, path);
    std::cout << "Chargement du modele termine" << std::endl;
}

void Model::Draw(std::shared_ptr<Shader>& shader, const glm::mat4& model, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPosition, const std::vector<std::shared_ptr<Light>>& lightArray)
{
    for (auto& mesh : m_meshes)
    {
        //std::cout << m_path << std::endl;
        mesh.prepareMesh(shader, viewProjMatrix, cameraPosition, lightArray);
        mesh.applyMeshTransformation(shader, model);
        mesh.Draw();
        mesh.releaseMesh(shader);
    }
}

void Model::DrawInstanced(std::shared_ptr<Shader>& shader, const glm::mat4& viewProjMatrix, const glm::vec3& cameraPosition, const unsigned int& count, const std::vector<std::shared_ptr<Light>>& lightArray)
{
    for (auto& mesh : m_meshes)
    {
        mesh.prepareMesh(shader, viewProjMatrix, cameraPosition, lightArray);
        mesh.DrawInstanced(count);
        mesh.releaseMesh(shader);
    }
}

void Model::loadModel(Assimp::Importer& importer, std::string const& path)
{
    const aiScene* scene{ importer.ReadFile(path, aiProcessPreset_TargetRealtime_Fast | aiProcess_ConvertToLeftHanded) };

    // Gestion des erreurs
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Erreur Assimp : " << importer.GetErrorString() << std::endl;
        return;
    }

    // Recuperer le dossier de notre modele
    m_directory = path.substr(0, path.find_last_of('/'));
    m_path = path;

    // Parcourir chaque noeud du modele recursivement
    processNode(scene->mRootNode, scene, glm::mat4(1.0));

    importer.FreeScene();
}

void Model::processNode(aiNode* node, const aiScene* scene, glm::mat4 parent_transform)
{
    // Convertir les transformations stockees dans une aiMat4 en glm::mat4
    glm::mat4 globalTransform = AiMatrix4x4ToGlm(&node->mTransformation) * parent_transform;

    // Parcourir chaque maille sur le noeud actuel
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh{ scene->mMeshes[node->mMeshes[i]] };
        Mesh mesh = processMesh(assimpMesh, scene);

        // Ajouter les transformations du modele enregistrees dans le fichier
        mesh.setTransformation(globalTransform);
        m_meshes.push_back(mesh);
    }

    // Parcourir chaque noeud enfant par rapport a celui-ci
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, globalTransform);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // Donnees qui seront stockes dans la mesh fraîchement creee
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::weak_ptr<TextureFile>> textures;

    // Passer a travers l'ensemble des sommets de la mesh
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // Pour convertir les vec3 de Assimp en glm::vec3

        if (mesh->HasPositions())
        {
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
        }
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        if (mesh->HasTextureCoords(0)) // Si la mesh contient des TexCoords
        {
            glm::vec2 vec;
            // Une texture peut avoir jusqu'a 8 TexCoords differents, ici on considere seulement qu'il n'en existe qu'une (0)
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        if (mesh->HasTangentsAndBitangents())
        {
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }

        // On ajoute le Vertex avec les infos remplies
        vertices.push_back(vertex);
    }

    // Recuperer les indices de la maille
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face{ mesh->mFaces[i] };
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material{ scene->mMaterials[mesh->mMaterialIndex] };

    //On recupere l'opacite de la prochaine texture
    float opacity{ 1.f };
    material->Get(AI_MATKEY_OPACITY, opacity);

    // Vecteur pour les textures deja chargees de la maille
    std::vector<std::weak_ptr<TextureFile>> textureLoaded;

    // Recuperer l'ensemble des textures
    // 1. diffuse maps
    loadMaterialTextures(scene, material, aiTextureType_DIFFUSE, textures, textureLoaded);
    // 2. specular maps
    loadMaterialTextures(scene, material, aiTextureType_SPECULAR, textures, textureLoaded);
    // 3. normal maps
    loadMaterialTextures(scene, material, aiTextureType_NORMALS, textures, textureLoaded);
    // 4. height maps
    loadMaterialTextures(scene, material, aiTextureType_HEIGHT, textures, textureLoaded);
    // 5. emissive maps
    loadMaterialTextures(scene, material, aiTextureType_EMISSIVE, textures, textureLoaded);
    // 6. ambient maps
    loadMaterialTextures(scene, material, aiTextureType_AMBIENT, textures, textureLoaded);

    return Mesh(vertices, indices, textures, opacity);
}

void Model::loadMaterialTextures(const aiScene* scene, aiMaterial* mat, aiTextureType type, std::vector<std::weak_ptr<TextureFile>>& texturesVector, std::vector<std::weak_ptr<TextureFile>>& textureLoaded)
{
    // On recupere le TextureManager
    auto textureManager{ TextureManager::getInstance() };
    bool srgb = true;

    // Definir le type de texture a enregistrer
    TextureType texType;
    switch (type)
    {
        case aiTextureType_DIFFUSE:
            texType = Texture_DIFFUSE;
        break;
        case aiTextureType_SPECULAR:
            texType = Texture_SPECULAR;
        break;
        case aiTextureType_AMBIENT:
            texType = Texture_AMBIENT;
        break;
        case aiTextureType_EMISSIVE:
            texType = Texture_EMISSIVE;
        break;
        case aiTextureType_HEIGHT:
            texType = Texture_HEIGHT;
            srgb = false;
        break;
        case aiTextureType_NORMALS:
            texType = Texture_NORMAL;
            srgb = false;
        break;
        default:
            throw std::runtime_error("Impossible de trouver le type de texture");
        break;
    }

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip{ false };

        for (std::weak_ptr<TextureFile> texturePtr : textureLoaded)
        {
            auto texture{ texturePtr.lock() };
            if (std::strcmp(texture->getTexturePath().data(), str.C_Str()) == 0)
            {
                texturesVector.push_back(texture);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            std::string name = std::string(str.C_Str()) + std::to_string(texType) + std::to_string(i);
            std::weak_ptr<TextureFile> texturePtr{ textureManager->createTextureFile(name, std::string(this->m_directory + "/" + str.C_Str()), texType, this->m_flipTexture, srgb) };
            texturesVector.push_back(texturePtr);
            textureLoaded.push_back(texturePtr);
        }
    }
}

//https://stackoverflow.com/questions/73611341/assimp-gltf-meshes-not-properly-scaled
glm::mat4 Model::AiMatrix4x4ToGlm(const aiMatrix4x4* from)
{
    glm::mat4 to;

    to[0][0] = (GLfloat)from->a1; to[0][1] = (GLfloat)from->b1;  to[0][2] = (GLfloat)from->c1; to[0][3] = (GLfloat)from->d1;
    to[1][0] = (GLfloat)from->a2; to[1][1] = (GLfloat)from->b2;  to[1][2] = (GLfloat)from->c2; to[1][3] = (GLfloat)from->d2;
    to[2][0] = (GLfloat)from->a3; to[2][1] = (GLfloat)from->b3;  to[2][2] = (GLfloat)from->c3; to[2][3] = (GLfloat)from->d3;
    to[3][0] = (GLfloat)from->a4; to[3][1] = (GLfloat)from->b4;  to[3][2] = (GLfloat)from->c4; to[3][3] = (GLfloat)from->d4;

    return to;
}