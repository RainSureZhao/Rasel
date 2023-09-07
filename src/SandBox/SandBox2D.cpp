//
// Created by 赵润朔 on 2023/9/1.
//

#include "SandBox2D.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

#include "stdafx.h"

SandBox2D::SandBox2D() : Layer("SandBox2D"), m_CameraController(1280.0f / 720.0f){
}

void SandBox2D::OnAttach() {
    RZ_PROFILE_FUNCTION();
    std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
    m_CheckerboardTexture = Rasel::Texture2D::Create(R"(assets/textures/Checkerboard.png)");
}

void SandBox2D::OnDetach() {
    RZ_PROFILE_FUNCTION();
}

void SandBox2D::OnUpdate(Rasel::Timestep ts) {


    RZ_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(ts);
    
    //Render
    {
        RZ_PROFILE_SCOPE("Renderer Prep");
        Rasel::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Rasel::RendererCommand::Clear();
    }
    {
        RZ_PROFILE_SCOPE("Renderer Draw");
        Rasel::Renderer2D::BeginScene(m_CameraController.GetCamera());
        // Rasel::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
        Rasel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        // Rasel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
        Rasel::Renderer2D::EndScene();
    }
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("Setting");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void SandBox2D::OnEvent(Rasel::Event &e) {
    m_CameraController.OnEvent(e);
}
