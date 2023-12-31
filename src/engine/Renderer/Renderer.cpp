//
// Created by 赵润朔 on 2023/8/1.
//

#include "Renderer.h"
#include "OpenGLShader.h"
#include "Core.h"
#include "Renderer2D.h"

namespace Rasel {

    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
    
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
        RZ_PROFILE_FUNCTION();
        RendererCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RendererCommand::SetViewPort(0, 0, width, height);
    }

    void Renderer::Shutdown() {
        Renderer2D::Shutdown();
    }


} // Rasel