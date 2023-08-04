//
// Created by 赵润朔 on 2023/8/4.
//

#include "stdafx.h"
#include "RendererCommand.h"
#include "OpenGLRendererAPI.h"

namespace Rasel {
    
    RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
    
} // Rasel