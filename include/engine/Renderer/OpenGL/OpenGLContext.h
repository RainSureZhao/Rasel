//
// Created by 赵润朔 on 2023/7/29.
//

#ifndef RASEL_OPENGLCONTEXT_H
#define RASEL_OPENGLCONTEXT_H

#include "GraphicsContext.h"

struct GLFWwindow;

namespace Rasel {

    class OpenGLContext : public GraphicsContext{
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        
        virtual void Init() override;
        virtual void SwapBuffers() override;
        
    private:
        GLFWwindow* m_WindowHandle;
    };

} // Rasel

#endif //RASEL_OPENGLCONTEXT_H
