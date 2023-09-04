//
// Created by 赵润朔 on 2023/8/3.
//

#ifndef RASEL_OPENGLVERTEXARRAY_H
#define RASEL_OPENGLVERTEXARRAY_H

#include "VertexArray.h"

namespace Rasel {

    class OpenGLVertexArray : public VertexArray{
    public:
        OpenGLVertexArray();
        
        virtual ~OpenGLVertexArray() override;
        
        virtual void Bind() const override;
        virtual void UnBind() const override;
        
        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
        
        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override {
            return m_VertexBuffers;
        }
        
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const override {
            return m_IndexBuffer;
        }
        
    private:
        uint32_t m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };

} // Rasel

#endif //RASEL_OPENGLVERTEXARRAY_H
