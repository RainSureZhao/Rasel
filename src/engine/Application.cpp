//
// Created by 赵润朔 on 2023/7/16.
//
        
#include "Application.h"
#include "ApplicationEvent.h"
#include "Log.h"
#include "GLFW/glfw3.h"
namespace Rasel{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    std::shared_ptr<Application> Application::s_Instance = nullptr;
    Application::Application()
    {
        RZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = std::shared_ptr<Application>(this);
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }
    
    Application::~Application() = default;
    
    void Application::Run() {
        while(m_Running) {
            glClearColor(0.2, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            for(auto &layer : m_LayerStack)
                layer->OnUpdate();
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);
            if(e.Handled)
                break;
        }
        RZ_CORE_TRACE("{0}", e);
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(std::unique_ptr<Layer> layer) {
        layer->OnAttach();
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PushOverlay(std::unique_ptr<Layer> overlay) {
        overlay->OnAttach();
        m_LayerStack.PushOverlay(std::move(overlay));
    }
}
