//
// Created by 赵润朔 on 2023/9/2.
//

#include "stdafx.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "OpenGLShader.h"
#include "RendererCommand.h"


namespace Rasel {
    struct Renderer2DStorage {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> FlatColorShader;
    };
    
    Scope<Renderer2DStorage> s_Data;
    
    void Renderer2D::Init() {
        s_Data = CreateScope<Renderer2DStorage>();
        s_Data->QuadVertexArray = VertexArray::Create();
        
        std::vector<float> squareVertices{
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        
        auto squareVB = VertexBuffer::Create(squareVertices.data(), sizeof(float) * squareVertices.size());
        squareVB->SetLayout({
            {"a_Position", ShaderDataType::Float3}
        });
        s_Data->QuadVertexArray->AddVertexBuffer(squareVB);
        
        std::vector<uint32_t> squareIndices {
            0, 1, 2, 2, 3, 0
        };
        auto squareIB = IndexBuffer::Create(squareIndices.data(), squareVertices.size());
        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
        std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
        s_Data->FlatColorShader = Shader::Create(R"(shader/FlatColor.glsl)");
    }

    void Renderer2D::Shutdown() {

    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera) {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene() {

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Rasel::OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);
        
        s_Data->QuadVertexArray->Bind();
        RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
} // Rasel