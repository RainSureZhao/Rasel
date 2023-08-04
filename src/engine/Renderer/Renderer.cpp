//
// Created by 赵润朔 on 2023/8/1.
//

#include "Renderer.h"

namespace Rasel {

    void Renderer::BeginScene() {
        
    }
    
    void Renderer::EndScene() {
        
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
    
    
} // Rasel