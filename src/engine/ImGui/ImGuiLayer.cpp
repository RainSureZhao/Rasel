//
// Created by 赵润朔 on 2023/7/25.
//

#include "ImGuiLayer.h"
#include "Application.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glfw/glfw3.h"

namespace Rasel {
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

    ImGuiLayer::~ImGuiLayer() = default;
    
    void ImGuiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        
        
        ImGuiIO& io = ImGui::GetIO();
        (void)io; // 消除编译器产生的未使用变量的警告
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 启用键盘控制
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // 启用手柄控制
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // 启用Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // 启用多窗口
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons; // 禁用多窗口任务栏图标
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge; // 禁用多窗口合并

        ImGui::StyleColorsDark();
        
        ImGuiStyle& style = ImGui::GetStyle();
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        
        auto& app = Application::Get();
        auto window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
        
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        
        ImGui_ImplOpenGL3_Init("#version 410");
    }
    
    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnImGuiRender() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        auto& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
        
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    


} // Rasel