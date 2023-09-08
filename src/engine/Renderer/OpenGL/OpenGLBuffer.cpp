//
// Created by 赵润朔 on 2023/8/1.
//

#include "OpenGLBuffer.h"
#include "glad/glad.h"
namespace Rasel {
    
    // VertexBuffer
    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
        RZ_PROFILE_FUNCTION();
        
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        RZ_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }
    
    void OpenGLVertexBuffer::Bind() const {
        RZ_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }
    
    void OpenGLVertexBuffer::UnBind() const {
        RZ_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
        RZ_PROFILE_FUNCTION();
        
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size) {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    // IndexBuffer
    
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : m_Count(count) {
        RZ_PROFILE_FUNCTION();
        
        glCreateBuffers(1, &m_RendererID);
        // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
        // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(count * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
    }
    
    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        RZ_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }
    
    void OpenGLIndexBuffer::Bind() const {
        RZ_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }
    
    void OpenGLIndexBuffer::UnBind() const {
        RZ_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
} // Rasel