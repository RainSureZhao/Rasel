//
// Created by 赵润朔 on 2023/9/1.
//

#include "SandBox2D.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "OpenGLShader.h"
SandBox2D::SandBox2D() : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f){
}

void SandBox2D::OnAttach() {
    Rasel::Renderer2D::Init();
}

void SandBox2D::OnDetach() {
    
}

void SandBox2D::OnUpdate(Rasel::Timestep ts) {
    // Update
    m_CameraController.OnUpdate(ts);
    
    //Render
    Rasel::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Rasel::RendererCommand::Clear();
    
    Rasel::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Rasel::Renderer2D::DrawQuad({0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Rasel::Renderer2D::EndScene();
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("Setting");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void SandBox2D::OnEvent(Rasel::Event &e) {
    m_CameraController.OnEvent(e);
}
