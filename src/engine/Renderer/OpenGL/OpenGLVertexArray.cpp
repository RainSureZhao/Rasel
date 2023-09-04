//
// Created by 赵润朔 on 2023/8/3.
//

#include "stdafx.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"
#include "Core.h"

namespace Rasel {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch(type) {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
            case ShaderDataType::None:
                break;
        }

        RZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
    
    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &m_RendererID);
    }
    
    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_RendererID);
    }
    
    void OpenGLVertexArray::UnBind() const {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
        
        RZ_CORE_ASSERT(!vertexBuffer->GetLayout().GetElements().empty(), "Vertex Buffer has no layout!");
        
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();
        
        const auto& layout = vertexBuffer->GetLayout();
        for(const auto& element : layout) {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex,
              static_cast<GLint>(element.GetComponentCount()),
              ShaderDataTypeToOpenGLBaseType(element.Type),
              element.Normalized ? GL_TRUE : GL_FALSE,
              static_cast<GLint>(layout.GetStride()),
              reinterpret_cast<const void*>(element.Offset));
            m_VertexBufferIndex ++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }
    
    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
        
        m_IndexBuffer = indexBuffer;
    }
    
} // Rasel