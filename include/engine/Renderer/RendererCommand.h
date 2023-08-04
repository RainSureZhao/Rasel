//
// Created by 赵润朔 on 2023/8/4.
//

#ifndef RASEL_RENDERERCOMMAND_H
#define RASEL_RENDERERCOMMAND_H

#include "RendererAPI.h"

namespace Rasel {

    class RendererCommand {
    public:
        inline static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }
        
        inline static void Clear() {
            s_RendererAPI->Clear();
        }
        
        inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };

} // Rasel

#endif //RASEL_RENDERERCOMMAND_H
