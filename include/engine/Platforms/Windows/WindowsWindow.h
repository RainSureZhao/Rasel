//
// Created by 赵润朔 on 2023/7/22.
//

#ifndef RASEL_WINDOWSWINDOW_H
#define RASEL_WINDOWSWINDOW_H

#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Log.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "MouseEvent.h"


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
        
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
        
    private:
        GLFWwindow * m_Window;
        
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
