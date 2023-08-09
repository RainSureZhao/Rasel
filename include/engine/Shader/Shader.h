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
        Shader() = default;
        virtual ~Shader() = default;
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        
        static Shader* Create(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);
    };

} // Rasel

#endif //RASEL_SHADER_H
