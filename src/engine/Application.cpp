//
// Created by 赵润朔 on 2023/7/16.
//
        
#include "Application.h"
#include "Log.h"
#include "GLFW/glfw3.h"
#include "Core.h"
#include "Renderer.h"
#include "Instrumentor.h"

namespace Rasel{
    Scope<Application> Application::s_Instance = nullptr;
    
    
    Application::Application()
    {
        RZ_PROFILE_FUNCTION();
        RZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        std::filesystem::current_path(R"(E:\Code\Cpp_project\Rasel)");
        s_Instance = Rasel::Scope<Application>(this);
        m_Window = Window::Create();
        m_Window->SetEventCallback([this](auto && PH1) { Application::OnEvent(std::forward<decltype(PH1)>(PH1)); });
        
        Renderer::Init();
        
        m_ImGuiLayer = CreateScope<ImGuiLayer>();
        PushOverlay(std::move(m_ImGuiLayer));
    }
    
    void Application::Run() {
        while(m_Running) {
            const auto time = static_cast<float>(glfwGetTime());
            const Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            if(!m_Minimized) {
                for(auto &layer : m_LayerStack)
                    layer->OnUpdate(timestep);
            }
             m_ImGuiLayer->Begin();
            for(auto &layer : m_LayerStack)
                layer->OnImGuiRender();
             m_ImGuiLayer->End();
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        RZ_PROFILE_FUNCTION();
        EventDispatcher dispatcher(e);
        
        dispatcher.Dispatch<WindowCloseEvent>([this](auto &&PH1){ return OnWindowClosed(std::forward<decltype(PH1)>(PH1));});
        dispatcher.Dispatch<WindowResizeEvent>([this](auto &&PH1){ return OnWindowResize(std::forward<decltype(PH1)>(PH1));});
        
        if(m_LayerStack.size()) {
            for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
                (*--it)->OnEvent(e);
                if(e.Handled)
                    break;
            }
        }
        RZ_CORE_TRACE("{0}", e);
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Scope<Layer> layer) {
        RZ_PROFILE_FUNCTION();
        layer->OnAttach();
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(Scope<Layer> overlay) {
        RZ_PROFILE_FUNCTION();
        overlay->OnAttach();
        m_LayerStack.PushOverlay(std::move(overlay));
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
        if(e.GetWidth() == 0 or e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        
        return false;
    }

    Application::~Application() {
        RZ_PROFILE_FUNCTION();
        Renderer::Shutdown();
    }
}
