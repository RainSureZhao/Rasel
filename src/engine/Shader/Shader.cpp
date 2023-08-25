//
// Created by 赵润朔 on 2023/7/30.
//

#include "Shader.h"
#include "Log.h"
#include "Renderer.h"
#include "OpenGLShader.h"

namespace Rasel {
    Shader *Shader::Create(const std::string &vertexShaderFile, const std::string &fragmentShaderFile) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexShaderFile, fragmentShaderFile);
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Shader *Shader::Create(const std::string &filepath) {
        switch(RendererAPI::GetAPI()) {
            case RendererAPI::API::None: 
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(filepath);
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // Rasel