//
// Created by 赵润朔 on 2023/9/6.
//
#include "Window.h"
#include "Log.h"



#ifdef RZ_PLATFORM_WINDOWS
    #include "WindowsWindow.h"
#endif

namespace Rasel {
    Scope<Window> Window::Create(const Rasel::WindowProps &props) {
        #ifdef RZ_PLATFORM_WINDOWS
            return CreateScope<WindowsWindow>(props);
        #else
            RZ_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }
}