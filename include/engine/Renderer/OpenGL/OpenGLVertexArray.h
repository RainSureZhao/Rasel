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
        
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
        
        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override {
            return m_VertexBuffers;
        }
        
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override {
            return m_IndexBuffer;
        }
        
    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };

} // Rasel

#endif //RASEL_OPENGLVERTEXARRAY_H
