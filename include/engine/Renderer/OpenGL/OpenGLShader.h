//
// Created by 赵润朔 on 2023/8/9.
//

#ifndef RASEL_OPENGLSHADER_H
#define RASEL_OPENGLSHADER_H
#include "Shader.h"
#include "glm/glm.hpp"

namespace Rasel {

    class OpenGLShader : public Shader{
    public:
        OpenGLShader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

        virtual ~OpenGLShader() override;
        
        virtual void Bind() const override;
        virtual void UnBind() const override;
        
        void UploadUniformInt(const std::string& name, int value) const;
        void UploadUniformFloat(const std::string& name, float value) const;
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const;
        
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
    private:
        uint32_t m_RendererID;
    };

} // Rasel

#endif //RASEL_OPENGLSHADER_H
