//
// Created by 赵润朔 on 2023/7/22.
//

#ifndef RASEL_WINDOW_H
#define RASEL_WINDOW_H

#include "stdafx.h"
#include "Event.h"

namespace Rasel {
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        
        explicit WindowProps(const std::string &title = "Rasel Engine", 
                    unsigned int width = 1280, unsigned int height = 720) : Title(title), Width(width), Height(height) {}
    };
    
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        
        virtual ~Window()  = default;
        virtual void OnUpdate() = 0;
        
        [[nodiscard]] virtual unsigned int GetWidth() const = 0;
        [[nodiscard]] virtual unsigned int GetHeight() const = 0;
        
        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        [[nodiscard]] virtual bool IsVSync() const = 0;
        
        static Window* Create(const WindowProps& props = WindowProps());
    };
}

#endif //RASEL_WINDOW_H
