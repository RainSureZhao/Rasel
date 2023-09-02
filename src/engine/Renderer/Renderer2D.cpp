//
// Created by 赵润朔 on 2023/9/2.
//

#include "stdafx.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "OpenGLShader.h"
#include "RendererCommand.h"
#include "glm/ext/matrix_transform.hpp"


namespace Rasel {
    struct Renderer2DStorage {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> FlatColorShader;
        Ref<Shader> TextureShader;
    };
    
    Scope<Renderer2DStorage> s_Data;
    
    void Renderer2D::Init() {
        s_Data = CreateScope<Renderer2DStorage>();
        s_Data->QuadVertexArray = VertexArray::Create();
        
        std::vector<float> squareVertices{
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        
        auto squareVB = VertexBuffer::Create(squareVertices.data(), sizeof(float) * squareVertices.size());
        squareVB->SetLayout({
            {"a_Position", ShaderDataType::Float3},
            {"a_TexCoord", ShaderDataType::Float2}
        });
        s_Data->QuadVertexArray->AddVertexBuffer(squareVB);
        
        std::vector<uint32_t> squareIndices {
            0, 1, 2, 2, 3, 0
        };
        auto squareIB = IndexBuffer::Create(squareIndices.data(), squareVertices.size());
        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
        std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
        s_Data->FlatColorShader = Shader::Create(R"(shader/FlatColor.glsl)");
        
        s_Data->TextureShader = Shader::Create(R"(shader/Texture.glsl)");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown() {

    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera) {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {

    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        s_Data->FlatColorShader->Bind();
        s_Data->FlatColorShader->SetFloat4("u_Color", color);
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_Data->FlatColorShader->SetMat4("u_Transform", transform);
        
        s_Data->QuadVertexArray->Bind();
        RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture) {
        DrawQuad({position.x, position.y, 0.0f}, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture) {
        s_Data->TextureShader->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_Data->TextureShader->SetMat4("u_Transform", transform);
        
        texture->Bind();
        
        s_Data->QuadVertexArray->Bind();
        RendererCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
} // Rasel