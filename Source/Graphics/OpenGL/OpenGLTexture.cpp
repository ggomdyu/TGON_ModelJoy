#include "PrecompiledHeader.h"

#if TGON_GRAPHICS_OPENGL
#include "Misc/Algorithm.h"

#include "OpenGLDebug.h"

#include "../Texture.h"

namespace tgon
{
namespace
{

constexpr GLint ConvertTextureFilterModeToNative(FilterMode textureFilterMode) noexcept
{
    constexpr GLint nativeTextureFilterModes[] = {
        GL_NEAREST,
        GL_LINEAR
    };
    return nativeTextureFilterModes[UnderlyingCast(textureFilterMode)];
}
    
constexpr GLint ConvertTextureWrapModeToNative(WrapMode textureWrapMode) noexcept
{
    constexpr GLint nativeTextureWrapModes[] = {
        GL_REPEAT,
        GL_CLAMP_TO_EDGE,
        GL_MIRRORED_REPEAT,
    };
    return nativeTextureWrapModes[UnderlyingCast(textureWrapMode)];
}

constexpr GLenum ConvertPixelFormatToNative(PixelFormat pixelFormat) noexcept
{
    constexpr GLenum nativePixelFormats[] = {
        0,
        GL_RGBA,
        GL_RGB,
        GL_RGB4,
        GL_RED,
    };              
    return nativePixelFormats[UnderlyingCast(pixelFormat)];
}

GLuint CreateTextureHandle()
{
    GLuint textureHandle;
    TGON_GL_ERROR_CHECK(glGenTextures(1, &textureHandle));

    return textureHandle;
}

GLuint CreatePixelBufferHandle(GLsizeiptr bufferBytes)
{
    GLuint pixelBufferHandle = 0;

    TGON_GL_ERROR_CHECK(glGenBuffers(1, &pixelBufferHandle));
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixelBufferHandle));
    TGON_GL_ERROR_CHECK(glBufferData(GL_PIXEL_UNPACK_BUFFER, bufferBytes, nullptr, GL_STATIC_DRAW));
    TGON_GL_ERROR_CHECK(glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0));

    return pixelBufferHandle;
}

} /* namespace */

OpenGLTexture::OpenGLTexture() noexcept :
    m_textureHandle(CreateTextureHandle())
{
}

OpenGLTexture::OpenGLTexture(OpenGLTexture&& rhs) noexcept :
    m_textureHandle(rhs.m_textureHandle)
{
    rhs.m_textureHandle = 0;
}

OpenGLTexture::~OpenGLTexture()
{
    this->Destroy();
}

OpenGLTexture& OpenGLTexture::operator=(OpenGLTexture&& rhs) noexcept
{
    this->Destroy();

    m_textureHandle = rhs.m_textureHandle;

    rhs.m_textureHandle = 0;

    return *this;
}

void OpenGLTexture::Use()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    this->UpdateTexParameters();
}

void OpenGLTexture::Unuse()
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

void OpenGLTexture::CreateMipmap() const
{
    TGON_GL_ERROR_CHECK(glGenerateMipmap(GL_TEXTURE_2D));
}

GLuint OpenGLTexture::GetTextureHandle() const noexcept
{
    return m_textureHandle;
}

void OpenGLTexture::Destroy()
{
    if (m_textureHandle != 0)
    {
        TGON_GL_ERROR_CHECK(glDeleteTextures(1, &m_textureHandle));
        m_textureHandle = 0;
    }
}

void OpenGLTexture::UpdateTexParameters()
{
    // Update the texture filter
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // When Magnifying the image
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertTextureFilterModeToNative(reinterpret_cast<Texture*>(this)->GetFilterMode()))); // When minifying the image

    // Update the texture wrap mode
    auto wrapMode = ConvertTextureWrapModeToNative(reinterpret_cast<Texture*>(this)->GetWrapMode());
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode));
    TGON_GL_ERROR_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode));
}

Texture::Texture(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat, FilterMode filterMode, WrapMode wrapMode, bool isUseMipmap, bool isDynamicUsage) :
    OpenGLTexture(),
    m_isUseMipmap(isUseMipmap),
    m_isDynamicUsage(isDynamicUsage),
    m_pixelFormat(pixelFormat),
    m_filterMode(filterMode),
    m_wrapMode(wrapMode),
    m_size(size)
{
    this->SetData(imageData, size, pixelFormat);
}

bool Texture::IsValid() const
{
    return glIsTexture(m_textureHandle);
}

void Texture::SetData(const std::byte* imageData, const I32Extent2D& size, PixelFormat pixelFormat)
{
    auto nativePixelFormat = ConvertPixelFormatToNative(pixelFormat);
    
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, nativePixelFormat, size.width, size.height, 0, nativePixelFormat, GL_UNSIGNED_BYTE, imageData));

    if (m_isUseMipmap)
    {
        this->CreateMipmap();
    }
}

void Texture::SetData(const std::byte* imageData, const Vector2& pos, const I32Extent2D& size, PixelFormat pixelFormat)
{
    TGON_GL_ERROR_CHECK(glBindTexture(GL_TEXTURE_2D, m_textureHandle));
    TGON_GL_ERROR_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(pos.x), static_cast<GLint>(pos.y), static_cast<GLsizei>(size.width), static_cast<GLsizei>(size.height), ConvertPixelFormatToNative(pixelFormat), GL_UNSIGNED_BYTE, &imageData[0]));

    if (m_isUseMipmap)
    {
        this->CreateMipmap();
    }
}

} /* namespace tgon */
#endif
