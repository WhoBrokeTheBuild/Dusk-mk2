#ifndef DUSK_GRAPHICS_SPRITE_HPP
#define DUSK_GRAPHICS_SPRITE_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Graphics/Actor.hpp>
#include <Dusk/Graphics/Texture.hpp>
#include <Dusk/Geometry/Rect.hpp>
#include <Dusk/Geometry/Vector2.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Types.hpp>

#include <SFML/Graphics/Sprite.hpp>

namespace dusk
{

class Sprite : public Actor
{
public:
    DUSK_CLASSNAME("Sprite")

    inline Sprite(shared_ptr<Texture> pTexture)
        : mp_Texture(pTexture)
        , m_SfSprite()
    {
        m_SfSprite.setTexture(mp_Texture->GetSFMLTexture());
    }

    virtual inline ~Sprite() = default;

    virtual inline Vector2f GetPosition() const override { return m_SfSprite.getPosition(); }
    virtual inline void SetPosition(const Vector2f& pos) override { m_SfSprite.setPosition(pos); }

    virtual inline Vector2f GetScale() const override { return m_SfSprite.getScale(); }
    virtual inline void SetScale(const Vector2f& scale) override { m_SfSprite.setScale(scale); }

    virtual inline float GetRotation() const override { return m_SfSprite.getRotation(); }
    virtual inline void SetRotation(const float& rot) override { m_SfSprite.setRotation(rot); }

    inline Color GetColor() const override { return m_SfSprite.getColor(); }
    inline void SetColor(const Color& color) override { m_SfSprite.setColor(color); };

    virtual void Draw(GraphicsContext* pCtx) override;

    inline const sf::Sprite& GetSFMLSprite() const { return m_SfSprite; }

private:
    shared_ptr<Texture> mp_Texture;

    sf::Sprite m_SfSprite;

public:
    static void Script_RegisterFunctions() { }

}; // class Sprite

} // namespace dusk

#endif // DUSK_GRAPHICS_SPRITE_HPP
