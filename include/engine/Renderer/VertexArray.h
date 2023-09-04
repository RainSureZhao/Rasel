//
// Created by 赵润朔 on 2023/8/3.
//

#ifndef RASEL_VERTEXARRAY_H
#define RASEL_VERTEXARRAY_H

#include <memory>
#include "Buffer.h"
#include "Core.h"

namespace Rasel {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;
        
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        
        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
        
        [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        [[nodiscard]] virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
        
        static Ref<VertexArray> Create();
    };

} // Rasel

#endif //RASEL_VERTEXARRAY_H
