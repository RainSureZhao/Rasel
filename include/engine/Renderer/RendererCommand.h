//
// Created by 赵润朔 on 2023/8/4.
//

#ifndef RASEL_RENDERERCOMMAND_H
#define RASEL_RENDERERCOMMAND_H

#include "RendererAPI.h"
#include "Core.h"

namespace Rasel {

    class RendererCommand {
    public:
        static void Init() {
            s_RendererAPI->Init();
        }
        
        static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RendererAPI->SetViewPort(x, y, width, height);
        }
        
        static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }
        
        static void Clear() {
            s_RendererAPI->Clear();
        }
        
        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0) {
            s_RendererAPI->DrawIndexed(vertexArray, count);
        }
    private:
        static Scope<RendererAPI> s_RendererAPI;
    };

} // Rasel

#endif //RASEL_RENDERERCOMMAND_H
