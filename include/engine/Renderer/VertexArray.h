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
        
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
        
        [[nodiscard]] virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        [[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
        
        static Ref<VertexArray> Create();
    };

} // Rasel

#endif //RASEL_VERTEXARRAY_H
