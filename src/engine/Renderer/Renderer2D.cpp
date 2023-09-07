//
// Created by 赵润朔 on 2023/9/2.
//

#include "stdafx.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RendererCommand.h"
#include "glm/ext/matrix_transform.hpp"


namespace Rasel {
    struct QuadVertex {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        // TODO: texid
        float TexIndex;
        float TilingFactor;
    };
    
    struct Renderer2DData {
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTextureSlots = 32;
        
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;
        
        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
        
        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0 = white texture
    };
    
    static Renderer2DData s_Data;
    
    void Renderer2D::Init() {
        RZ_PROFILE_FUNCTION();
        s_Data.QuadVertexArray = VertexArray::Create();
        
        s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
        s_Data.QuadVertexBuffer->SetLayout({
            {"a_Position", ShaderDataType::Float3},
            {"a_Color", ShaderDataType::Float4},
            {"a_TexCoord", ShaderDataType::Float2},
            {"a_TexIndex", ShaderDataType::Float},
            {"a_TilingFactor", ShaderDataType::Float}
        });
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
        
        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
        
        auto quadIndices = new uint32_t[s_Data.MaxIndices];
        
        uint32_t offset = 0;
        for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;
            
            offset += 4;
        }
        Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;
        
        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTexture = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteTexture, sizeof(uint32_t));
        
        int32_t samplers[Rasel::Renderer2DData::MaxTextureSlots];
        for(uint32_t i = 0; i < Rasel::Renderer2DData::MaxTextureSlots; i ++) {
            samplers[i] = static_cast<int32_t>(i);
        }
        
        s_Data.TextureShader = Shader::Create("shader/Texture.glsl");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetIntArray("u_Texture", samplers, Rasel::Renderer2DData::MaxTextureSlots);
        
        // Set first texture slot to 0
        s_Data.TextureSlots[0] = s_Data.WhiteTexture;
    }

    void Renderer2D::Shutdown() {
        RZ_PROFILE_FUNCTION();
        
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera) {
        RZ_PROFILE_FUNCTION();

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
        
        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene() {
        RZ_PROFILE_FUNCTION();
        uint32_t dataSize = reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferPtr) - reinterpret_cast<uint8_t*>(s_Data.QuadVertexBufferBase);
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
        
        Flush();
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        RZ_PROFILE_FUNCTION();
        
        const float texIndex = 0.0f; // White Texture
        const float tilingFactor = 1.0f;
        
        s_Data.QuadVertexBufferPtr->Position = position;
        s_Data.QuadVertexBufferBase->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr ++;
        
        s_Data.QuadVertexBufferPtr->Position = {position.x + size.x, position.y, 0.0f};
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 0.0f};
        s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr ++;
        
        s_Data.QuadVertexBufferPtr->Position = {position.x + size.x, position.y + size.y, 0.0f};
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {1.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr ++;
        
        s_Data.QuadVertexBufferPtr->Position = {position.x, position.y + size.y, 0.0f};
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = {0.0f, 1.0f};
        s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr ++;
        
        s_Data.QuadIndexCount += 6;
    }
    

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture,
                              float tilingFactor, const glm::vec4 &tintColor) {
        DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);

    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture,
                              float tilingFactor, const glm::vec4 &tintColor) {
        RZ_PROFILE_FUNCTION();
        constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        
        float textureIndex = 0.0f;
        for(uint32_t i = 1; i < s_Data.TextureSlotIndex; i ++) {
            if(*s_Data.TextureSlots[i].get() == *texture.get()) {
                textureIndex = static_cast<float>(i);
                break;
            }
        }
        
        if(textureIndex == 0.0f) {
            textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex ++;
        }

        s_Data.QuadVertexBufferPtr->Position = position;
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

#if OLD_PATH
        s_Data.TextureShader->SetFloat4("u_Color", tintColor);
        s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
        texture->Bind();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_Data.TextureShader->SetMat4("u_Transform", transform);
        
        s_Data.QuadVertexArray->Bind();
        RendererCommand::DrawIndexed(s_Data.QuadVertexArray);
#endif
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                     const glm::vec4 &color) {
        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                     const glm::vec4 &color) {
        RZ_PROFILE_FUNCTION();
        
        s_Data.TextureShader->SetFloat4("u_Color", color);
        s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
        s_Data.WhiteTexture->Bind();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
                * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) 
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        
        s_Data.TextureShader->SetMat4("u_Transform", transform);
        s_Data.QuadVertexArray->Bind();
        RendererCommand::DrawIndexed(s_Data.QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation,
                                     const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor) {
        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation,
                                     const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor) {
        RZ_PROFILE_FUNCTION();
        
        s_Data.TextureShader->SetFloat4("u_Color", tintColor);
        s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
        texture->Bind();
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) 
                * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) 
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        
        s_Data.TextureShader->SetMat4("u_Transform", transform);
        
        s_Data.QuadVertexArray->Bind();
        RendererCommand::DrawIndexed(s_Data.QuadVertexArray);
    }

    void Renderer2D::Flush() {
        // Bind Textures
        for(uint32_t i = 0; i < s_Data.TextureSlotIndex; i ++) {
            s_Data.TextureSlots[i]->Bind(i);
        }
        
        RendererCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    }
} // Rasel