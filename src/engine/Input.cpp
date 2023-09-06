//
// Created by 赵润朔 on 2023/9/6.
//
#include "Input.h"
#include "Log.h"



#ifdef RZ_PLATFORM_WINDOWS
    #include "WindowsInput.h"
#endif

namespace Rasel {
    Scope<Input> Input::s_Instance = Input::Create();
    
    Scope<Input> Input::Create() {
        #ifdef RZ_PLATFORM_WINDOWS
            return CreateScope<WindowsInput>();
        #else
            RZ_CORE_ASSERT(false, "Unknown platform!");
            return nullptr;
        #endif
    }
}