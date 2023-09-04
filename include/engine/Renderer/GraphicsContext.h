//
// Created by 赵润朔 on 2023/7/29.
//

#ifndef RASEL_GRAPHICSCONTEXT_H
#define RASEL_GRAPHICSCONTEXT_H

#include "Window.h"

namespace Rasel {
    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
        
        static Scope<GraphicsContext> Create(void* window);
    };
}

#endif //RASEL_GRAPHICSCONTEXT_H
