//
// Created by 赵润朔 on 2023/8/18.
//
#define STB_IMAGE_IMPLEMENTATION
#include "stdafx.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "Log.h"

namespace Rasel {
    OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_Path(path){
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        RZ_CORE_ASSERT(data, "Failed to load image!");
        m_Width = width, m_Height = height;
        
        GLenum internalFormat = 0, dataFormat = 0;
        if(channels == 4) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        } else if(channels == 3) {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        
        m_InternalFormat = internalFormat, m_DataFormat = dataFormat;
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, static_cast<int>(m_Width), static_cast<int>(m_Height));
        
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTextureSubImage2D(m_RendererID, 0, 0, 0, static_cast<int>(m_Width), static_cast<int>(m_Height), dataFormat, GL_UNSIGNED_BYTE, data);
        
        stbi_image_free(data);
    }
    
    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_RendererID);
    }
    
    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(slot, m_RendererID);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height){
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, static_cast<int>(m_Width), static_cast<int>(m_Height));

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void OpenGLTexture2D::SetData(void *Data, uint32_t size) {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        RZ_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, static_cast<int>(m_Width), static_cast<int>(m_Height), m_DataFormat, GL_UNSIGNED_BYTE, Data);
    }
} // Rasel