//
// Created by 赵润朔 on 2023/8/1.
//

#include "Renderer.h"

namespace Rasel {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
    
    void Renderer::BeginScene(OrthographicCamera& camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();    
    }
    
    void Renderer::EndScene() {
        
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
    
    
} // Rasel