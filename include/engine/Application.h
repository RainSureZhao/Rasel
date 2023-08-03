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
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

namespace Rasel {
    class Application {
    public:
        Application();
        virtual ~Application() = default;
        void OnEvent(Event& e);
        void Run();
        
        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> overlay);
        
        inline Window& GetWindow() { return *m_Window; }
        
        inline static Application& Get() { return *s_Instance;}
        
    private:
        bool OnWindowClosed(WindowCloseEvent& e);
        
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<Shader> m_Shader;
        
        std::shared_ptr<Shader> m_BlueShader;
        std::shared_ptr<VertexArray> m_SquareVA;
    private:
        static std::shared_ptr<Application> s_Instance;
    };    
    
    // To be defined in CLIENT
    std::unique_ptr<Application> CreateApplication();
}




#endif //RASEL_APPLICATION_H
