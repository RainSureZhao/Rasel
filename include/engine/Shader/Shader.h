//
// Created by 赵润朔 on 2023/7/30.
//

#ifndef RASEL_SHADER_H
#define RASEL_SHADER_H
#include <stdafx.h>
#include "glm/glm.hpp"
namespace Rasel {

    class Shader {
    public:
        Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~Shader();
        
        void Bind() const;
        void UnBind() const;
        
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t m_RendererID;
    };

} // Rasel

#endif //RASEL_SHADER_H
