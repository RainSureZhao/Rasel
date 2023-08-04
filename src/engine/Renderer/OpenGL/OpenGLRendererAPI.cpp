//
// Created by 赵润朔 on 2023/8/4.
//

#include "stdafx.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Rasel {
    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
} // Rasel