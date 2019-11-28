#include "PrecompiledHeader.h"

#include "Text/Encoding.h"

#include "UIText.h"

namespace tgon
{

class TextBlock final
{
/**@section Struct */
public:
    struct LineInfo
    {
        int32_t characterStartIndex;
        int32_t characterEndIndex;
        I32Rect contentRect;
    };
    
/**@section Constructor */
public:
    TextBlock() = default;
    TextBlock(const gsl::span<const char32_t>& characters, const std::shared_ptr<UIFont>& font, int32_t fontSize, const I32Rect& rect, LineBreakMode lineBreakMode, TextAlignment textAlignment) noexcept;
    
/**@section Method */
public:
    void Initialize(const gsl::span<const char32_t>& characters, const std::shared_ptr<UIFont>& font, int32_t fontSize, const I32Rect& rect, LineBreakMode lineBreakMode, TextAlignment textAlignment) noexcept;
    void Clear();
    const I32Rect& GetRect() const noexcept;
    const I32Rect& GetContentRect() const noexcept;
    const std::vector<UIText::CharacterInfo>& GetCharacterInfos() const noexcept;
    
private:
    int32_t TryAddTextLine(const gsl::span<const char32_t>& characters, const std::shared_ptr<UIFont>& font, int32_t fontSize, const I32Rect& rect);
    void PopBackLine();
    void ProcessTextAlignment(TextAlignment textAlignment);
    void ProcessLineBreakMode(LineBreakMode lineBreakMode);
    
/**@section Variable */
private:
    I32Rect m_rect;
    I32Rect m_contentRect;
    std::vector<UIText::CharacterInfo> m_characterInfos;
    std::vector<LineInfo> m_lineInfos;
    int32_t m_iterIndex = 0;
};

TextBlock::TextBlock(const gsl::span<const char32_t>& characters, const std::shared_ptr<UIFont>& font, int32_t fontSize, const I32Rect& rect, LineBreakMode lineBreakMode, TextAlignment textAlignment) noexcept :
    m_rect(rect),
    m_contentRect(rect.x, rect.y, 0, 0)
{
    // TODO: First of all, we must check whether the text spill over.

    gsl::span<const char32_t> charactersSpan = characters;
    while (true)
    {
        bool isTextSpillOver = m_contentRect.height > rect.height;
        if (isTextSpillOver)
        {
            this->PopBackLine();
            break;
        }

        m_lineInfos.push_back(LineInfo{0, 0, I32Rect(rect.x, rect.y - m_contentRect.height, 0, 0)});

        int32_t insertedCharacterLen = this->TryAddTextLine(charactersSpan, font, fontSize, rect);
        if (insertedCharacterLen == 0)
        {
            this->PopBackLine();
            break;
        }

        charactersSpan = charactersSpan.subspan(insertedCharacterLen);
    }
    
    // The default text alignment mode is upper left,
    // so if the desired text alignment mode is the same, then ignore the realignment.
    if (textAlignment != TextAlignment::UpperLeft)
    {
        this->ProcessTextAlignment(textAlignment);
    }
}

void TextBlock::Initialize(const gsl::span<const char32_t>& characters, const std::shared_ptr<UIFont>& font, int32_t fontSize, const I32Rect& rect, LineBreakMode lineBreakMode, TextAlignment textAlignment) noexcept
{
    this->Clear();
    
    new (this) TextBlock(characters, font, fontSize, rect, lineBreakMode, textAlignment);
}

void TextBlock::Clear()
{
    m_rect = {};
    m_contentRect = {};
    m_characterInfos.clear();
    m_lineInfos.clear();
    m_iterIndex = 0;
}

const I32Rect& TextBlock::GetRect() const noexcept
{
    return m_rect;
}

const I32Rect& TextBlock::GetContentRect() const noexcept
{
    return m_contentRect;
}

const std::vector<UIText::CharacterInfo>& TextBlock::GetCharacterInfos() const noexcept
{
    return m_characterInfos;
}

void TextBlock::PopBackLine()
{
    if (m_lineInfos.empty())
    {
        return;
    }
    
    auto& backLineInfo = m_lineInfos.back();
    m_characterInfos.erase(m_characterInfos.begin() + backLineInfo.characterStartIndex, m_characterInfos.begin() + backLineInfo.characterEndIndex);
    m_contentRect.width = 0;
    for (auto& lineInfo : m_lineInfos)
    {
        m_contentRect.width = std::max(m_contentRect.width, lineInfo.contentRect.width);
    }
    m_contentRect.height -= backLineInfo.contentRect.height;
    m_lineInfos.pop_back();
}

int32_t TextBlock::TryAddTextLine(const gsl::span<const char32_t>& characters, const std::shared_ptr<UIFont>& font, int32_t fontSize, const I32Rect& rect)
{
    int32_t yMin = INT32_MAX;
    int32_t yMax = -INT32_MAX;
    int32_t yMaxBearing = -INT32_MAX;
    int32_t insertedTextLen = static_cast<int32_t>(characters.size());
    int32_t characterStartIndex = m_iterIndex;
    int32_t xAdvance = 0;
    
    auto& lineInfo = m_lineInfos.back();
    
    for (size_t i = 0; i < characters.size(); ++i)
    {
        auto ch = characters[i];
        
        const auto& glyphData = font->GetGlyphData(ch, fontSize);
        if (rect.width < xAdvance + glyphData.metrics.size.width)
        {
            insertedTextLen = static_cast<int32_t>(i);
            break;
        }

        I32Vector2 characterPos{rect.x + xAdvance + glyphData.metrics.bearing.x, rect.y + glyphData.metrics.bearing.y - m_contentRect.height};
        m_characterInfos.push_back({glyphData.ch, {characterPos.x, characterPos.y, glyphData.metrics.size.width, glyphData.metrics.size.height}});
        
        yMin = std::min(yMin, characterPos.y - glyphData.metrics.size.height);
        yMax = std::max(yMax, characterPos.y);
        yMaxBearing = std::max(yMaxBearing, glyphData.metrics.bearing.y);
        
        xAdvance += glyphData.metrics.advance.x;
        m_iterIndex += 1;
    }

    if (insertedTextLen > 0)
    {
        lineInfo.characterStartIndex = characterStartIndex;
        lineInfo.characterEndIndex = m_iterIndex;
        
        // Refresh the content rect of line.
        int32_t lineHeight = yMax - yMin;
        const auto& frontCharacterInfo = m_characterInfos[lineInfo.characterStartIndex];
        const auto& backCharacterInfo = m_characterInfos[std::max(lineInfo.characterStartIndex, lineInfo.characterEndIndex - 1)];
        lineInfo.contentRect.height = lineHeight;
        lineInfo.contentRect.width = (backCharacterInfo.rect.x + backCharacterInfo.rect.width) - frontCharacterInfo.rect.x;
        
        // Refresh the content rect of total text block.
        m_contentRect.height += lineHeight;
        m_contentRect.width = std::max(m_contentRect.width, lineInfo.contentRect.width);
    
        for (int32_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
        {
            m_characterInfos[i].rect.y -= yMaxBearing;
        }
    }
    
    return insertedTextLen;
}

void TextBlock::ProcessTextAlignment(TextAlignment textAlignment)
{
    switch (textAlignment)
    {
    case TextAlignment::LowerLeft:
        {
            int32_t yOffset = m_rect.y - m_rect.height + m_contentRect.height;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::LowerCenter:
        {
            int32_t yOffset = m_rect.y - m_rect.height + m_contentRect.height;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + (m_rect.width - lineInfo.contentRect.width) / 2;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::LowerRight:
        {
            int32_t yOffset = m_rect.y - m_rect.height + m_contentRect.height;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + m_rect.width - lineInfo.contentRect.width;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;

    case TextAlignment::MiddleLeft:
        {
            int32_t yOffset = m_rect.y - ((m_rect.height - m_contentRect.height) / 2);
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;

    case TextAlignment::MiddleCenter:
        {
            int32_t yOffset = m_rect.y - (m_rect.height - m_contentRect.height) / 2;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + (m_rect.width - lineInfo.contentRect.width) / 2;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::MiddleRight:
        {
            int32_t yOffset = m_rect.y - ((m_rect.height - m_contentRect.height) / 2);
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + m_rect.width - lineInfo.contentRect.width;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;

    case TextAlignment::UpperLeft:
        {
            int32_t yOffset = m_rect.y;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::UpperCenter:
        {
            int32_t yOffset = m_rect.y;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + (m_rect.width - lineInfo.contentRect.width) / 2;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
            
    case TextAlignment::UpperRight:
        {
            int32_t yOffset = m_rect.y;
            for (auto& lineInfo : m_lineInfos)
            {
                int32_t xOffset = m_rect.x + m_rect.width - lineInfo.contentRect.width;
                for (size_t i = lineInfo.characterStartIndex; i != lineInfo.characterEndIndex; ++i)
                {
                    m_characterInfos[i].rect.x = xOffset + (m_characterInfos[i].rect.x - lineInfo.contentRect.x);
                    m_characterInfos[i].rect.y = yOffset - (lineInfo.contentRect.y - m_characterInfos[i].rect.y);
                }
                lineInfo.contentRect.x = xOffset;
                lineInfo.contentRect.y = yOffset;
                yOffset -= lineInfo.contentRect.height;
            }
        }
        break;
    }
}

UIText::UIText() noexcept :
    m_textBlock(std::make_unique<TextBlock>())
{
}

UIText::~UIText() = default;

UIText::UIText(UIText&& rhs) noexcept :
    m_text(std::move(rhs.m_text)),
    m_font(std::move(rhs.m_font)),
    m_fontSize(rhs.m_fontSize),
    m_textAlignment(rhs.m_textAlignment),
    m_lineSpacing(rhs.m_lineSpacing),
    m_lineBreakMode(rhs.m_lineBreakMode),
    m_color(rhs.m_color),
    m_rect(rhs.m_rect),
    m_isDirty(rhs.m_isDirty),
    m_textBlock(std::move(rhs.m_textBlock))
{
}

UIText& UIText::operator=(UIText&& rhs) noexcept
{
    m_text = std::move(rhs.m_text);
    m_font = std::move(rhs.m_font);
    m_fontSize = rhs.m_fontSize;
    m_textAlignment = rhs.m_textAlignment;
    m_lineSpacing = rhs.m_lineSpacing;
    m_lineBreakMode = rhs.m_lineBreakMode;
    m_color = rhs.m_color;
    m_rect = rhs.m_rect;
    m_isDirty = rhs.m_isDirty;
    m_textBlock = std::move(rhs.m_textBlock);
    
    rhs.m_fontSize = {};
    rhs.m_textAlignment = TextAlignment::UpperLeft;
    rhs.m_lineSpacing = {};
    rhs.m_lineBreakMode = LineBreakMode::CharacterWrap;
    rhs.m_color = {};
    rhs.m_rect = {};
    rhs.m_isDirty = true;
    
    return *this;
}

void UIText::SetFont(const std::shared_ptr<UIFont>& font)
{
    m_font = font;
    m_isDirty = true;
}

void UIText::SetFontSize(int32_t fontSize)
{
    m_fontSize = fontSize;
    m_isDirty = true;
}

void UIText::SetText(const std::string_view& text)
{
    m_text = text;
    m_isDirty = true;
}

void UIText::SetTextAlignment(TextAlignment textAlignment)
{
    m_textAlignment = textAlignment;
    m_isDirty = true;
}

void UIText::SetLineSpacing(float lineSpacing)
{
    m_lineSpacing = lineSpacing;
    m_isDirty = true;
}

void UIText::SetLineBreakMode(LineBreakMode lineBreakMode)
{
    m_lineBreakMode = lineBreakMode;
    m_isDirty = true;
}

void UIText::SetColor(const Color4f& color)
{
    m_color = color;
    m_isDirty = true;
}

void UIText::SetRect(const I32Rect& rect)
{
    m_rect = rect;
    m_isDirty = true;
}

std::shared_ptr<UIFont> UIText::GetFont() noexcept
{
    return m_font;
}

std::shared_ptr<const UIFont> UIText::GetFont() const noexcept
{
    return m_font;
}

int32_t UIText::GetFontSize() const noexcept
{
    return m_fontSize;
}

const std::string& UIText::GetText() const noexcept
{
    return m_text;
}

TextAlignment UIText::GetTextAlignment() const noexcept
{
    return m_textAlignment;
}

float UIText::GetLineSpacing() const noexcept
{
    return m_lineSpacing;
}

LineBreakMode UIText::GetLineBreakMode() const noexcept
{
    return m_lineBreakMode;
}

const Color4f& UIText::GetColor() const noexcept
{
    return m_color;
}

const I32Rect& UIText::GetRect() const noexcept
{
    return m_rect;
}

const std::vector<UIText::CharacterInfo>& UIText::GetCharacterInfos() const noexcept
{
    if (m_isDirty)
    {
        auto characters = Encoding::UTF8().GetChars(reinterpret_cast<const std::byte*>(&m_text[0]), static_cast<int32_t>(m_text.length()));
        
        m_textBlock->Initialize(characters, m_font, m_fontSize, m_rect, m_lineBreakMode, m_textAlignment);
        m_font->Insert(characters, m_fontSize);
        
        m_isDirty = false;
    }
    
    return m_textBlock->GetCharacterInfos();
}

void UIText::GetBatches(std::vector<UIBatch>* batches, const Matrix4x4& matWorld, std::vector<float>* vertices) const
{
    UIBatch batch(m_font->GetAtlasTexture(), FilterMode::Bilinear, WrapMode::Clamp, BlendMode::Alpha, false, {}, static_cast<int32_t>(vertices->size()));
    if (batches->empty() || batches->back().CanBatch(batch) == false)
    {
        batches->push_back(batch);
    }

    for (const auto& characterInfo : this->GetCharacterInfos())
    {
        auto optTextureRect = m_font->GetTextureRect(characterInfo.character);
        if (optTextureRect.has_value() == false)
        {
            continue;
        }
        
        const FRect& textureRect = (*optTextureRect).get();
        batches->back().Merge(float(characterInfo.rect.x), float(characterInfo.rect.y), textureRect, Vector2(0.0f, 0.0f), Color4f(1.0f, 1.0f, 1.0f, 1.0f), matWorld, vertices);
    }
}

} /* namespace tgon */
