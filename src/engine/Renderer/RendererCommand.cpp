//
// Created by 赵润朔 on 2023/8/4.
//

#include "RendererCommand.h"
#include "OpenGLRendererAPI.h"

namespace Rasel {
    
    Scope<RendererAPI> RendererCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
    
} // Rasel