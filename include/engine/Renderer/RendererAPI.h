//
// Created by 赵润朔 on 2023/8/4.
//

#ifndef RASEL_RENDERERAPI_H
#define RASEL_RENDERERAPI_H

#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Rasel {

    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL = 1
        };
    public:
        virtual ~RendererAPI() = default;
        
        virtual void Init() = 0;
        virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
        
        inline static API GetAPI() {return s_API;}
        
        static Scope<RendererAPI> Create();
        
    private:
        static API s_API;
    };

} // Rasel

#endif //RASEL_RENDERERAPI_H
