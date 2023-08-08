//
// Created by 赵润朔 on 2023/8/1.
//

#ifndef RASEL_RENDERER_H
#define RASEL_RENDERER_H

#include "RendererCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "glm/glm.hpp"
namespace Rasel {
    
    class Renderer {
    public:
        static void BeginScene(OrthographicCamera& camera);
        
        static void EndScene();
        
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
        
        inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}
       
    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };
        
        static SceneData* s_SceneData;
    };

} // Rasel

#endif //RASEL_RENDERER_H
