#pragma once

#include "../OpenGLObject.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader : public OpenGLObject
{
    private:
        // Fonction de debug pour verifier la compilation du shader
        // --------------------------------------------------------
        void checkCompileErrors(GLuint shader, std::string type);

    public:
        // Constructeur qui genere le programme de shading directement
        // -----------------------------------------------------------
        Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
        ~Shader();

        // Activer le shader
        // -----------------
        void Bind() override;
        void Unbind() override;
        void Delete() override;

        // Fonctions pour les uniforms
        // ---------------------------
        void setBool(const std::string& name, bool value) const;
        // ------------------------------------------------------------------------
        void setInt(const std::string& name, int value) const;
        // ------------------------------------------------------------------------
        void setFloat(const std::string& name, float value) const;
        // ------------------------------------------------------------------------
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        // ------------------------------------------------------------------------
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        // ------------------------------------------------------------------------
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w);
        // ------------------------------------------------------------------------
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
};