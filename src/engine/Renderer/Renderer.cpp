//
// Created by 赵润朔 on 2023/8/1.
//

#include "Renderer.h"

namespace Rasel {

    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
    
    void Renderer::BeginScene(OrthographicCamera& camera) {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();    
    }
    
    void Renderer::EndScene() {
        
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
    
    
} // Rasel