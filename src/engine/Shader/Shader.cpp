//
// Created by 赵润朔 on 2023/7/30.
//

#include "Shader.h"
#include "glad/glad.h"
#include "Log.h"
namespace Rasel {
    Rasel::Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc) {
        auto VertexShader = glCreateShader(GL_VERTEX_SHADER);
        auto FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        
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

    Rasel::Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    void Rasel::Shader::Bind() const {
        glUseProgram(m_RendererID);
    }

    void Rasel::Shader::UnBind() const {
        glUseProgram(0);
    }
} // Rasel