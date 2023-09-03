//
// Created by 赵润朔 on 2023/8/18.
//

#ifndef RASEL_OPENGLTEXTURE_H
#define RASEL_OPENGLTEXTURE_H
#include "Texture.h"
#include "glad/glad.h"

namespace Rasel {

    class OpenGLTexture2D : public Texture2D{
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();
        
        [[nodiscard]] virtual uint32_t GetWidth() const override { return m_Width;}
        [[nodiscard]] virtual uint32_t GetHeight() const override { return m_Height;}
        
        virtual void SetData(void* Data, uint32_t size) override;
        
        virtual void Bind(uint32_t slot = 0) const override;
    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };

} // Rasel

#endif //RASEL_OPENGLTEXTURE_H
