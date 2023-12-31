//
// Created by 赵润朔 on 2023/7/22.
//

#include "WindowsWindow.h"
#include "stdafx.h"
#include "OpenGLContext.h"
#include "ApplicationEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "Log.h"
#include "KeyCodes.h"
#include "MouseCodes.h"

namespace Rasel {
    static uint8_t s_GLFWWindowCount = 0;
    
    static void GLFWErrorCallback(int error, const char* description) {
        RZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }
    
    WindowsWindow::WindowsWindow(const WindowProps& props) {
        Init(props);
    }
    
    WindowsWindow::~WindowsWindow() noexcept {
        Shutdown();
    }
    
    void WindowsWindow::Init(const WindowProps &props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        
        RZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
        
        if(s_GLFWWindowCount == 0) {
            int success = glfwInit();
            RZ_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }
        {
            RZ_PROFILE_FUNCTION();
        #if defined(RZ_DEBUG)
                if(Renderer::GetAPI() == RendererAPI::API::OpenGL)
                    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);    
        #endif
            m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(), nullptr, nullptr);
            s_GLFWWindowCount ++;
        }

        m_Context = CreateScope<OpenGLContext>(m_Window);
        m_Context->Init();
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
        
        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
            
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            data.EventCallback(event);
        });
        
        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch(action)
            {
                case GLFW_PRESS: {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(static_cast<KeyCode>(key));
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(static_cast<KeyCode>(key), 1);
                    data.EventCallback(event);
                    break;
                }
                default: {
                    break;
                }
            }
        });
        
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch(action)
            {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                    data.EventCallback(event);
                    break;
                }
                default: {
                    break;
                }
            }
        });
        
        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.EventCallback(event);
        });
        
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            data.EventCallback(event);
        });
        
        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
           WindowData &data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
           
           KeyTypedEvent event(static_cast<KeyCode>(keycode));
           data.EventCallback(event);
        });
    }
    
    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
        s_GLFWWindowCount --;
        if(s_GLFWWindowCount == 0) {
            RZ_CORE_INFO("Terminating GLFW");
            glfwTerminate();
        }
    }
    
    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }
    
    void WindowsWindow::SetVSync(bool enabled) {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        
        m_Data.VSync = enabled;
    }
    
    bool WindowsWindow::IsVSync() const {
        return m_Data.VSync;
    }
} // Rasel