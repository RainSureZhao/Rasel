//
// Created by 赵润朔 on 2023/8/1.
//

#ifndef RASEL_OPENGLBUFFER_H
#define RASEL_OPENGLBUFFER_H
#include "Buffer.h"

namespace Rasel {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();
        
        virtual void Bind() const;
        virtual void UnBind() const;
        
    private:
        uint32_t m_RendererID;
    };
    
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        
        virtual ~OpenGLIndexBuffer();
        
        virtual void Bind() const;
        virtual void UnBind() const;
        
        [[nodiscard]] virtual uint32_t GetCount() const {
            return m_Count;
        }
        
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

} // Rasel

#endif //RASEL_OPENGLBUFFER_H
