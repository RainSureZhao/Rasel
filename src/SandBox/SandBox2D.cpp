//
// Created by 赵润朔 on 2023/9/1.
//

#include "SandBox2D.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "OpenGLShader.h"
#include "stdafx.h"
#include "RendererCommand.h"
#include "Renderer.h"

SandBox2D::SandBox2D() : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f){
}

void SandBox2D::OnAttach() {
    std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
    
    m_SquareVA = Rasel::VertexArray::Create();
    
    std::vector<float> vertices {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    
    Rasel::Ref<Rasel::VertexBuffer> squareVB;
    squareVB.reset(Rasel::VertexBuffer::Create(vertices.data(), sizeof(float) * vertices.size()));
    squareVB->SetLayout({
        {"a_Position", Rasel::ShaderDataType::Float3}
    });
    m_SquareVA->AddVertexBuffer(squareVB);
    
    std::vector<uint32_t> squareIndices {
        0, 1, 2, 2, 3, 0
    };
    Rasel::Ref<Rasel::IndexBuffer> squareIB;
    squareIB.reset(Rasel::IndexBuffer::Create(squareIndices.data(), sizeof(float) * squareIndices.size()));
    m_SquareVA->SetIndexBuffer(squareIB);
    
    m_FlatColorShader = Rasel::Shader::Create(R"(shader/FlatColor.glsl)");
}

void SandBox2D::OnDetach() {
    
}

void SandBox2D::OnUpdate(Rasel::Timestep ts) {
    // Update
    m_CameraController.OnUpdate(ts);
    
    //Render
    Rasel::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Rasel::RendererCommand::Clear();
    
    Rasel::Renderer::BeginScene(m_CameraController.GetCamera());
    
    std::dynamic_pointer_cast<Rasel::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Rasel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
    
    Rasel::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    
    Rasel::Renderer::EndScene();
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("Setting");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void SandBox2D::OnEvent(Rasel::Event &e) {
    m_CameraController.OnEvent(e);
}
