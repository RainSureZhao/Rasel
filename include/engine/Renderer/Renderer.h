//
// Created by 赵润朔 on 2023/8/1.
//

#ifndef RASEL_RENDERER_H
#define RASEL_RENDERER_H

namespace Rasel {

    enum class RendererAPI {
        None = 0, OpenGL = 1
    };
    
    class Renderer {
    public:
        inline static RendererAPI GetAPI() {
            return s_RendererAPI;
        }
    private:
        static RendererAPI s_RendererAPI;
    };

} // Rasel

#endif //RASEL_RENDERER_H
