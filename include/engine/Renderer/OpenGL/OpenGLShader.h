//
// Created by 赵润朔 on 2023/8/9.
//

#ifndef RASEL_OPENGLSHADER_H
#define RASEL_OPENGLSHADER_H
#include "Shader.h"
#include "glm/glm.hpp"

using GLenum = unsigned int;
namespace Rasel {

    class OpenGLShader : public Shader{
    public:
        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name, const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

        virtual ~OpenGLShader() override;
        
        virtual void Bind() const override;
        virtual void UnBind() const override;


        virtual void SetInt(const std::string& name, int value) override;
        virtual void SetIntArray(const std::string& name, int* value, uint32_t count) override;
        virtual void SetFloat(const std::string& name, float value) override;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
        virtual void SetMat4(const std::string& name, const glm::mat4 &value) override;
        
        virtual const std::string& GetName() const override {return m_Name;}
        
        void UploadUniformInt(const std::string& name, int value) const;
        void UploadUniformIntArray(const std::string& name, int* value, uint32_t count) const;
        void UploadUniformFloat(const std::string& name, float value) const;
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const;
        
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const;
        
    private:
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };

} // Rasel

#endif //RASEL_OPENGLSHADER_H
