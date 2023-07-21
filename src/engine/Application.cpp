//
// Created by 赵润朔 on 2023/7/16.
//
        
#include "Application.h"
#include "ApplicationEvent.h"
#include "Log.h"
#include "Event.h"
namespace Rasel{
    Application::Application() = default;
    
    Application::~Application() = default;
    
    void Application::Run() {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication))
        {
            RZ_CORE_TRACE(e);
        }
        if (e.IsInCategory(EventCategoryInput))
        {
            RZ_CORE_TRACE(e);
        }
        while(true);
    }
}
