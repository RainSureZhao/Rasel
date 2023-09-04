//
// Created by 赵润朔 on 2023/9/4.
//

#include "Log.h"
#include "GraphicsContext.h"
#include "Renderer.h"
#include "OpenGLContext.h"

namespace Rasel {

    Scope<GraphicsContext> GraphicsContext::Create(void *window) {
        switch(Renderer::GetAPI()) {
            case RendererAPI::API::None:    RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}