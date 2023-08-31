//
// Created by 赵润朔 on 2023/7/22.
//

#ifndef RASEL_WINDOWSWINDOW_H
#define RASEL_WINDOWSWINDOW_H

#include "Window.h"
#include "GraphicsContext.h"
#include "GLFW/glfw3.h"
#include "Core.h"

namespace Rasel {

    class WindowsWindow : public Window {
    public:
        explicit WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow() noexcept;
        
        void OnUpdate() override;
        
        [[nodiscard]] unsigned int GetWidth() const override { return m_Data.Width; }
        [[nodiscard]] unsigned int GetHeight() const override { return m_Data.Height; }
        
        // Window attributes
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback;}
        void SetVSync(bool enabled) override;
        [[nodiscard]] bool IsVSync() const override;
        
        inline virtual void* GetNativeWindow() const override { return m_Window; }
        
    private:
        void Init(const WindowProps& props);
        void Shutdown();
        
    private:
        GLFWwindow * m_Window;
        Scope<GraphicsContext> m_Context;
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };
        
        WindowData m_Data;
    };

} // Rasel

#endif //RASEL_WINDOWSWINDOW_H
