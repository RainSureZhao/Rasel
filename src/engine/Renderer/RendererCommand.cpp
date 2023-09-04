//
// Created by 赵润朔 on 2023/8/4.
//

#include "RendererCommand.h"

namespace Rasel {
    
    Scope<RendererAPI> RendererCommand::s_RendererAPI = RendererAPI::Create();
    
} // Rasel