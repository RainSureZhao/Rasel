//
// Created by 赵润朔 on 2023/7/30.
//

#include "Shader.h"
#include "Log.h"
#include "Renderer.h"
#include "OpenGLShader.h"

namespace Rasel {
    Ref<Shader> Shader::Create(const std::string& name, const std::string &vertexShaderFile, const std::string &fragmentShaderFile) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(name, vertexShaderFile, fragmentShaderFile);
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string &filepath) {
        switch(RendererAPI::GetAPI()) {
            case RendererAPI::API::None: 
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(filepath);
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    void ShaderLibrary::Add(const Ref<Rasel::Shader> &shader) {
        auto& name = shader->GetName();
        m_Shader[name] = shader;
    }
    
    void ShaderLibrary::Add(const std::string &name, const Ref<Rasel::Shader> &shader) {
        RZ_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shader[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &filepath) {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name) {
        RZ_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shader[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) const {
        return m_Shader.find(name) != m_Shader.end();
    }
} // Rasel