//
// Created by 赵润朔 on 2023/7/30.
//

#ifndef RASEL_SHADER_H
#define RASEL_SHADER_H

#include "glm/glm.hpp"
#include <unordered_map>
#include "Core.h"

namespace Rasel {

    class Shader {
    public:
        Shader() = default;
        virtual ~Shader() = default;
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        
        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetIntArray(const std::string& name, int* value, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4 &value) = 0;
        
        virtual const std::string& GetName() const = 0;
        
        static Ref<Shader> Create(const std::string &filepath);
        static Ref<Shader> Create(const std::string& name, const std::string &vertexShaderFile, const std::string &fragmentShaderFile);
    };
    
    class ShaderLibrary{
    public:
        void Add(const std::string& name, const Ref<Shader>& shader);
        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filepath);
        Ref<Shader> Load(const std::string& name, const std::string& filepath);
        
        Ref<Shader> Get(const std::string& name);
        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shader;
    };

} // Rasel

#endif //RASEL_SHADER_H
