#include "SpriteText.hpp"

#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Geometry/Rect.hpp>

namespace dusk
{

void
SpriteText::SetFont(Font* pFont)
{
    mp_Font = pFont;
    if (mp_Font)
    {
        m_SfText.setFont(mp_Font->GetSFMLFont());
    }
}

void
SpriteText::SetText(const string& text)
{
    m_Text = text;
    m_SfText.setString(m_Text);
}

void
SpriteText::SetFontSize(const unsigned int& fontSize)
{
    m_FontSize = fontSize;
    m_SfText.setCharacterSize(fontSize);
}

Vector2f
SpriteText::GetSize() const
{
    FloatRect bounds = m_SfText.getLocalBounds();
    return Vector2f(
        bounds.left + bounds.left + bounds.width, bounds.top + bounds.top + bounds.height);
}

void
SpriteText::Draw(GraphicsContext* pCtx)
{
}

} // namespace dusk
