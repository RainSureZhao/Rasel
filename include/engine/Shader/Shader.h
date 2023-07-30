//
// Created by 赵润朔 on 2023/7/30.
//

#ifndef RASEL_SHADER_H
#define RASEL_SHADER_H
#include <stdafx.h>

namespace Rasel {

    class Shader {
    public:
        Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~Shader();
        
        void Bind() const;
        void UnBind() const;
        
    private:
        uint32_t m_RendererID;
    };

} // Rasel

#endif //RASEL_SHADER_H
