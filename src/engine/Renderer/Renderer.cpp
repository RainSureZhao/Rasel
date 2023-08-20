//
// Created by 赵润朔 on 2023/8/1.
//

#include "Renderer.h"
#include "OpenGLShader.h"
#include "Core.h"
namespace Rasel {

    Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;
    
    void Renderer::BeginScene(OrthographicCamera& camera) {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();    
    }
    
    void Renderer::EndScene() {
        
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }

    void Renderer::Init() {
        RendererCommand::Init();
    }


} // Rasel