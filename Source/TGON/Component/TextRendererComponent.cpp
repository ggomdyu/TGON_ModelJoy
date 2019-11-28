#include "PrecompiledHeader.h"

#include "Game/GameObject.h"
#include "Engine/GraphicsModule.h"

#include "Platform/Application.h"
#include "Engine/AssetModule.h"

#include "TextRendererComponent.h"

namespace tgon
{

TextRendererComponent::TextRendererComponent() :
    RendererComponent(),
    m_text(std::make_shared<UIText>())
{
}

void TextRendererComponent::SetFont(const char* fontPath)
{
    auto assetModule = Application::GetEngine()->FindModule<AssetModule>();
    this->SetFont(assetModule->GetFont(fontPath));
}

void TextRendererComponent::SetFont(const std::shared_ptr<UIFont>& font) noexcept
{
    m_text->SetFont(font);
}

void TextRendererComponent::SetText(const std::string_view& text)
{
    m_text->SetText(text);
}

void TextRendererComponent::SetFontSize(int32_t fontSize) noexcept
{
    m_text->SetFontSize(fontSize);
}

void TextRendererComponent::SetLineSpacing(float lineSpacing) noexcept
{
    m_text->SetLineSpacing(lineSpacing);
}

void TextRendererComponent::SetLineBreakMode(LineBreakMode lineBreakMode) noexcept
{
    m_text->SetLineBreakMode(lineBreakMode);
}

void TextRendererComponent::SetTextAlignment(TextAlignment textAlignment) noexcept
{
    m_text->SetTextAlignment(textAlignment);
}

void TextRendererComponent::SetColor(const Color4f& color) noexcept
{
    m_text->SetColor(color);
}

void TextRendererComponent::SetRect(const I32Rect& rect) noexcept
{
    m_text->SetRect(rect);
}

void TextRendererComponent::SetSortingLayer(int32_t sortingLayer) noexcept
{
    m_sortingLayer = sortingLayer;
}

LineBreakMode TextRendererComponent::GetLineBreakMode() const noexcept
{
    return m_text->GetLineBreakMode();
}

TextAlignment TextRendererComponent::GetTextAlignment() const noexcept
{
    return m_text->GetTextAlignment();
}

const Color4f& TextRendererComponent::GetColor() const noexcept
{
    return m_text->GetColor();
}

std::shared_ptr<const UIFont> TextRendererComponent::GetFont() const noexcept
{
    return m_text->GetFont();
}

std::shared_ptr<UIFont> TextRendererComponent::GetFont() noexcept
{
    return m_text->GetFont();
}

int32_t TextRendererComponent::GetFontSize() const noexcept
{
    return m_text->GetFontSize();
}

const I32Rect& TextRendererComponent::GetRect() const noexcept
{
    return m_text->GetRect();
}

int32_t TextRendererComponent::GetSortingLayer() const noexcept
{
    return m_sortingLayer;
}

void TextRendererComponent::Update()
{
    if (m_text->GetColor().a <= 0.0f)
    {
        return;
    }
    
    auto gameObject = m_gameObject.lock();
    if (gameObject != nullptr)
    {
        m_graphicsModule->GetUIRenderer().AddUIElement(m_text, m_sortingLayer, gameObject->GetComponent<Transform>()->GetWorldMatrix());
    }
}

} /* namespace tgon */
