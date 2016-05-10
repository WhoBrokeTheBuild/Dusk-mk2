#ifndef DUSK_GRAPHICS_SPRITE_TEXT_HPP
#define DUSK_GRAPHICS_SPRITE_TEXT_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Graphics/Actor.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Geometry/Vector2.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Text.hpp>

namespace dusk
{

class Font;

class SpriteText : public Actor
{

    friend class GraphicsContext;

public:
    DUSK_CLASSNAME("Sprite Text")

    SpriteText() = default;
    SpriteText(const SpriteText&) = default;
    SpriteText& operator=(const SpriteText&) = default;
    virtual ~SpriteText() = default;

    SpriteText(Font* pFont, const string& text, const unsigned int& fontSize,
        const Color& color)
    {
        SetFont(pFont);
        SetText(text);
        SetFontSize(fontSize);
        SetColor(color);
    }

    virtual inline Vector2f GetPosition() const override { return m_SfText.getPosition(); }
    virtual inline void SetPosition(const Vector2f& pos) override
    {
        return m_SfText.setPosition(pos);
    }

    virtual inline Vector2f GetScale() const override { return m_SfText.getScale(); }
    virtual inline void SetScale(const Vector2f& scale) override
    {
        return m_SfText.setScale(scale);
    }

    virtual inline float GetRotation() const override { return m_SfText.getRotation(); }
    virtual inline void SetRotation(const float& rot) override
    {
        return m_SfText.setRotation(rot);
    }

    virtual inline Color GetColor() const override { return m_SfText.getColor(); }
    virtual inline void SetColor(const Color& color) override { m_SfText.setColor(color); }

    void SetFont(Font* pFont);

    inline string GetText() const { return m_Text; }
    void SetText(const string& text);

    inline unsigned int GetFontSize() const { return m_FontSize; }
    void SetFontSize(const unsigned int& fontSize);

    Vector2f GetSize() const;

    virtual void Draw(GraphicsContext* pCtx) override;

    inline const sf::Text& GetSFMLText() const { return m_SfText; }

private:
    Font* mp_Font;

    string m_Text;

    unsigned int m_FontSize = 12;

    sf::Text m_SfText;

public:
    static void Script_RegisterFunctions() {}

}; // class SpriteText

} // namespace dusk

#endif // DUSK_GRAPHICS_TEXT_BUFFER_HPP
