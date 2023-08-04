//
// Created by 赵润朔 on 2023/8/3.
//

#include "stdafx.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "OpenGLVertexArray.h"
#include "Log.h"
namespace Rasel {
    VertexArray* VertexArray::Create() {
        switch(Renderer::GetAPI()) {
            case RendererAPI::API::None:
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexArray();
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // Rasel