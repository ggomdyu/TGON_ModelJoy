/**
 * @file    Sprite.h
 * @author  ggomdyu
 * @since   06/06/2018
 */

#pragma once
#include <memory>
#include <string>

#include "Core/Math/Rect.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Extent.h"

#include "../LowLevel/GraphicsType.h"

namespace tgon
{

class Texture;

class TGON_API Sprite final
{
/**@section Constructor */
public:
    explicit Sprite(const std::shared_ptr<Texture>& texture);
    Sprite(Sprite&& rhs);

/**@section Destructor */
public:
    virtual ~Sprite() = default;
    
/**@section Method */
public:
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;
    void SetTextureRect(const FRect& textureRect);
    FRect& GetTextureRect() noexcept;
    const FRect& GetTextureRect() const noexcept;
    void SetBlendMode(BlendMode blendMode) noexcept;
    BlendMode GetBlendMode() const noexcept;
    void SetScissorRect(const FRect& rect) noexcept;
    FRect& GetScissorRect() noexcept;
    const FRect& GetScissorRect() const noexcept;
    void SetLayer(int32_t layer) noexcept;
    int32_t GetLayer() const noexcept;
    
/**@section Variable */
private:
    std::shared_ptr<Texture> m_texture;
    BlendMode m_blendMode;
    FRect m_scissorRect;
    FRect m_textureRect;
    int32_t m_layer;
};

class NinePatchSprite
{
public:
private:
    Sprite m_sprites[9];
};
    
} /* namespace tgon */
