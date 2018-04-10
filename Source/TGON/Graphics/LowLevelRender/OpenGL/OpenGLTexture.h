/**
 * @filename    OpenGLTexture.h
 * @author      ggomdyu
 * @since       02/20/2018
 * @brief
 */

#pragma once
#include <GL/glew.h>

#include "../Generic/GenericTexture.h"

namespace tgon
{

class OpenGLTexture :
    public GenericTexture
{
/* @section Public constructor */
public:
    explicit OpenGLTexture(const std::string& filePath, const TextureCreateDesc& textureCreateDesc = {});

/* @section Public destructor */
public:
    virtual ~OpenGLTexture() override;

/* @section Public method */
public:
    virtual void TransferToVideo() final override;
    virtual void UpdateParemeters() final override;

    virtual void SetFilterMode(TextureFilterMode filterMode) final override;
    virtual void SetWrapMode(TextureWrapMode addressMode) final override;
    virtual TextureFilterMode GetFilterMode() const noexcept final override;
    virtual TextureWrapMode GetWrapMode() const noexcept final override;

private:
    GLuint GenerateTexture() const;
    void GenerateMipmap() const;

private:
    GLuint m_textureHandle;
    GLint m_filterMode;
    GLint m_wrapMode;
};

class Texture :
    public OpenGLTexture
{
/* @section Public constructor */
public:
    using OpenGLTexture::OpenGLTexture;

/* @section Public destructor */
public:
    virtual ~Texture() final override = default;
};

} /* namespace tgon */