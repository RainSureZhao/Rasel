//
// Created by 赵润朔 on 2023/7/16.
//

#ifndef RASEL_APPLICATION_H
#define RASEL_APPLICATION_H

#include "stdafx.h"
#include "Window.h"
#include "Event.h"
#include "ApplicationEvent.h"
namespace Rasel {
    class Application {
    public:
        Application();
        virtual ~Application();
        void OnEvent(Event& e);
        void Run();
    private:
        bool OnWindowClosed(WindowCloseEvent& e);
        
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };    
    
    // To be defined in CLIENT
    std::unique_ptr<Application> CreateApplication();
}




#endif //RASEL_APPLICATION_H
