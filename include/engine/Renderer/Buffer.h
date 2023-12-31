//
// Created by 赵润朔 on 2023/8/1.
//

#ifndef RASEL_BUFFER_H
#define RASEL_BUFFER_H

#include "stdafx.h"
#include "Log.h"
#include "Core.h"

namespace Rasel {
    
    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };
    
    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch(type) {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
            case ShaderDataType::None:
                break;
        }
        RZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
    
    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size{};
        uint32_t Offset{};
        bool Normalized{};
        
        BufferElement() = default;
        
        BufferElement(const std::string &name, ShaderDataType type, bool normalized = false) : Name(name), Type(type), Size(
                ShaderDataTypeSize(Type)), Offset(0), Normalized(normalized) {
            
        }
        
        [[nodiscard]] uint32_t GetComponentCount() const {
            switch(Type) {
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;
                case ShaderDataType::Mat3:      return 3;
                case ShaderDataType::Mat4:      return 4;
                case ShaderDataType::Int:       return 1;
                case ShaderDataType::Int2:      return 2;
                case ShaderDataType::Int3:      return 3;
                case ShaderDataType::Int4:      return 4;
                case ShaderDataType::Bool:      return 1;
                case ShaderDataType::None:
                    break;
            }
            RZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };
    
    class BufferLayout {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement> &elements) : m_Element(elements) {
            CalculateOffsetAndStride();
        }
        
        [[nodiscard]] uint32_t GetStride() const { return m_Stride;}
        [[nodiscard]] const std::vector<BufferElement>& GetElements() const {return m_Element;}
        
        std::vector<BufferElement>::iterator begin() { return m_Element.begin();}
        std::vector<BufferElement>::iterator end() { return m_Element.end();}
        [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const {return m_Element.begin(); }
        [[nodiscard]] std::vector<BufferElement>::const_iterator end() const {return m_Element.end(); }
        
        
    private:
        void CalculateOffsetAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;
            for(auto &element : m_Element) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
        
        
    private:
        std::vector<BufferElement> m_Element;
        uint32_t m_Stride = 0;
    };
    
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        
        virtual void SetData(const void* data, uint32_t size) = 0;
        
        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
        
        static Ref<VertexBuffer> Create(uint32_t size);
        static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };
    
    // currently only support 32-bit index buffer
    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;
        
        virtual void Bind() const = 0;  
        virtual void UnBind() const = 0;
        
        [[nodiscard]] virtual uint32_t GetCount() const = 0;
        
        static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };
}
#endif //RASEL_BUFFER_H
