//
// Created by 赵润朔 on 2023/8/1.
//

#include "Buffer.h"
#include "stdafx.h"
#include "Renderer.h"
#include "OpenGLBuffer.h"
#include "Log.h"
namespace Rasel {
    VertexBuffer* VertexBuffer::Create(float *vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);
        }       
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    
    IndexBuffer* IndexBuffer::Create(uint32_t *indices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None: 
                RZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, size);    
        }
        RZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}