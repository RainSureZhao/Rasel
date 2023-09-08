//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_APPLICATION_H
#define RASEL_APPLICATION_H

#include "stdafx.h"
#include "Window.h"
#include "Event.h"
#include "ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Input.h"
#include "ImGuiLayer.h"
#include "Timestep.h"
#include "Core.h"

int main(int argc, char** argv);

namespace Rasel {
    class Application {
    public:
        Application();
        virtual ~Application();
        void OnEvent(Event& e);
        
        void PushLayer(Scope<Layer> layer);
        void PushOverlay(Scope<Layer> overlay);
        
        Window& GetWindow() { return *m_Window; }
        
        static Application& Get() { return *s_Instance;}
        
    private:
        bool OnWindowClosed(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
        void Run();
        
        Scope<Window> m_Window;
        Scope<ImGuiLayer> m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
        
    private:
        static Scope<Application> s_Instance;
        friend int ::main(int argc, char** argv);
    };    
    
    // To be defined in CLIENT
    Scope<Application> CreateApplication();
}


#endif //RASEL_APPLICATION_H
