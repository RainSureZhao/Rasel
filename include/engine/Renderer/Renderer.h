//
// Created by 赵润朔 on 2023/8/1.
//

#ifndef RASEL_RENDERER_H
#define RASEL_RENDERER_H

#include "RendererCommand.h"

namespace Rasel {
    
    
    class Renderer {
    public:
        static void BeginScene();
        
        static void EndScene();
        
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        
        inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}
        
        
       
    };

} // Rasel

#endif //RASEL_RENDERER_H
