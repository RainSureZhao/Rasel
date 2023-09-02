//
// Created by 赵润朔 on 2023/9/2.
//

#ifndef RASEL_RENDERER2D_H
#define RASEL_RENDERER2D_H

#include "OrthographicCamera.h"

namespace Rasel {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();
        
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        
        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
    };

} // Rasel

#endif //RASEL_RENDERER2D_H
