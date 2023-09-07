//
// Created by 赵润朔 on 2023/8/9.
//

#include "OpenGLShader.h"
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"
#include "glad/glad.h"
#include <filesystem>
namespace Rasel {
    static GLenum ShaderTypeFromString(const std::string& type) {
        if(type == "vertex") return GL_VERTEX_SHADER;
        if(type == "fragment" or type == "pixel") return GL_FRAGMENT_SHADER;

        RZ_CORE_ASSERT(false, "Unknown shader type");
        return 0;
    }
    
    OpenGLShader::OpenGLShader(const std::string& name, const std::string &vertexShaderFile, const std::string &fragmentShaderFile) : m_Name(name) {
        RZ_PROFILE_FUNCTION();
        
        auto VertexShader = glCreateShader(GL_VERTEX_SHADER);
        auto FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        std::ifstream vertexFile(vertexShaderFile);
        std::ifstream shaderFile(fragmentShaderFile);

        std::string vertexSrc = std::string(std::istreambuf_iterator<char>(vertexFile), std::istreambuf_iterator<char>());
        std::string fragmentSrc = std::string(std::istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>());

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
    
    void OpenGLShader::UploadUniformIntArray(const std::string& name, int* value, uint32_t count) const {
        auto location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, count, value);
    }
    
    std::string OpenGLShader::ReadFile(const std::string &filepath) {
        std::ifstream FileSource(filepath);
        if(!FileSource.is_open()) {
            RZ_CORE_ERROR("Could not open file {0}", filepath);
            return {};
        }
        std::string Source = std::string(std::istreambuf_iterator<char>(FileSource), std::istreambuf_iterator<char>());
        return Source;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source) {
        std::unordered_map<GLenum, std::string> shaderSources;
        const std::string typeToken = "#type";
        auto pos = source.find(typeToken);
        while(pos != std::string::npos) {
            auto eol = source.find_first_of("\r\n", pos);
            RZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            auto begin = pos + typeToken.size() + 1;
            auto type = source.substr(begin, eol - begin);
            RZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");
            
            auto nextLinePos = source.find_first_not_of("\r\n", eol);
            RZ_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(typeToken, nextLinePos);
            
            shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }
        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources) {
        auto program = glCreateProgram();
        std::vector<GLenum> glShaderIDs;
        for(auto &[type, source] : shaderSources) {
            auto shader = glCreateShader(type);
            auto SourceStr = source.c_str();
            glShaderSource(shader, 1, &SourceStr, nullptr);
            
            glCompileShader(shader);
            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if(isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::string infoLog(maxLength, '\0');
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);
                RZ_CORE_ERROR("{0}", infoLog);
                RZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
                break;
            }
            glAttachShader(program, shader);
            glShaderIDs.push_back(shader);
        }
        m_RendererID = program;
        
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

            for(auto id : glShaderIDs) {
                glDeleteShader(id);
            }

            RZ_CORE_ERROR("{0}", infoLog);
            RZ_CORE_ASSERT(false, "Shader link failure!");
            return;
        }
        
        for(auto id : glShaderIDs) {
            glDetachShader(program, id);
            glDeleteShader(id);
        }
    }

    OpenGLShader::OpenGLShader(const std::string &filepath) {
        auto source = ReadFile(filepath);
        auto shaderSource = PreProcess(source);
        Compile(shaderSource);
        
        std::filesystem::path path = filepath;
        m_Name = path.stem().string();
    }

    void OpenGLShader::SetInt(const std::string &name, int value) {
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value) {
        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value) {
        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
        UploadUniformMat4(name, value);
    }

    void OpenGLShader::SetFloat(const std::string &name, float value) {
        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetIntArray(const std::string &name, int *value, uint32_t count) {
        UploadUniformIntArray(name, value, count);
    }
} // Rasel