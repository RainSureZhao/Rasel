//
// Created by 赵润朔 on 2023/8/18.
//

#include "Texture.h"
#include "Renderer.h"
#include "OpenGLTexture.h"
namespace Rasel {
    
    Ref<Texture2D> Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI())  {
            case RendererAPI::API::None:
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(path);   
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(width, height);        
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // Rasel