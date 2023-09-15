//
// Created by 赵润朔 on 2023/8/4.
//

#include "stdafx.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"
#include "Core.h"
#include "Log.h"

namespace Rasel {
    
    void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam) {
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                RZ_CORE_CRITICAL(message);
                return;
            case GL_DEBUG_SEVERITY_MEDIUM:
                RZ_CORE_ERROR(message);
                return;
            case GL_DEBUG_SEVERITY_LOW:
                RZ_CORE_WARN(message);
                return;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                RZ_CORE_TRACE(message);
                return;
        }
        RZ_CORE_ASSERT(false, "Unknown severity level!");
    }
    
    void OpenGLRendererAPI::Init() {
        RZ_PROFILE_FUNCTION();

    #ifdef RZ_DEBUG
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(OpenGLMessageCallback, nullptr);
            
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
    #endif
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }
    
    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount) {
        auto count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, static_cast<int>(count), GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height));
    }
} // Rasel