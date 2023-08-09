//
// Created by 赵润朔 on 2023/8/9.
//

#include "OpenGLShader.h"
#include "glad/glad.h"
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"

namespace Rasel {
    OpenGLShader::OpenGLShader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile) {
        auto VertexShader = glCreateShader(GL_VERTEX_SHADER);
        auto FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        std::ifstream vertexFile(vertexShaderFile);
        std::ifstream shaderFile(fragmentShaderFile);

        std::string vertexSrc = std::string((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
        std::string fragmentSrc = std::string((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

        const char* VertexSource = vertexSrc.c_str();
        const char* FragmentSource = fragmentSrc.c_str();

        glShaderSource(VertexShader, 1, &VertexSource, nullptr);
        glCompileShader(VertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::string infoLog(maxLength, '\0');
            glGetShaderInfoLog(VertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(VertexShader);
            RZ_CORE_ERROR("{0}", infoLog);
            RZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
            return;
        }

        glShaderSource(FragmentShader, 1, &FragmentSource, nullptr);

        glCompileShader(FragmentShader);
        glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if(isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::string infoLog(maxLength, '\0');
            glGetShaderInfoLog(FragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(FragmentShader);
            glDeleteShader(VertexShader);

            RZ_CORE_ERROR("{0}", infoLog);
            RZ_CORE_ASSERT(false, "Fragment shader compilation failure!");
            return;
        }

        m_RendererID = glCreateProgram();

        glAttachShader(m_RendererID, VertexShader);
        glAttachShader(m_RendererID, FragmentShader);

        glLinkProgram(m_RendererID);
        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
        if(isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::string infoLog(maxLength, '\0');
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_RendererID);

            glDeleteShader(VertexShader);
            glDeleteShader(FragmentShader);

            RZ_CORE_ERROR("{0}", infoLog);
            RZ_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        glDetachShader(m_RendererID, VertexShader);
        glDetachShader(m_RendererID, FragmentShader);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::UnBind() const {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value) const{
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, float value) const{
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &value) const {
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &value) const {
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &value) const {
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix) const {
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) const {
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
} // Rasel