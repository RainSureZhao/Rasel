//
// Created by 赵润朔 on 2023/8/4.
//

#ifndef RASEL_OPENGLRENDERERAPI_H
#define RASEL_OPENGLRENDERERAPI_H
#include "RendererAPI.h"

namespace Rasel {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void Init() override;
        
        virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
        
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

} // Rasel

#endif //RASEL_OPENGLRENDERERAPI_H
