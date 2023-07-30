//
// Created by 赵润朔 on 2023/7/29.
//

#include "OpenGLContext.h"
#include "Log.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Rasel {
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle){
        RZ_CORE_ASSERT(windowHandle, "Window handle is null!");    
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RZ_CORE_ASSERT(status, "Failed to initialize Glad!");
        
        RZ_CORE_INFO("OpenGL Info:");
        RZ_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        RZ_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        RZ_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
} // Rasel