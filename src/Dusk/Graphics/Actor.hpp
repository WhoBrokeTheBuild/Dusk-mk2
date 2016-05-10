#ifndef DUSK_GRAPHICS_ACTOR_HPP
#define DUSK_GRAPHICS_ACTOR_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Geometry/Vector2.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>

namespace dusk
{

class Actor : public TrackedObject
{
public:
    DUSK_CLASSNAME("Actor")

    virtual inline Vector2f GetPosition() const = 0;
    virtual inline void SetPosition(const Vector2f& pos) = 0;
    virtual inline void SetPosition(const float& x, const float& y) { SetPosition(Vector2f(x, y)); }

    virtual inline Vector2f GetScale() const = 0;
    virtual inline void SetScale(const Vector2f& scale) = 0;
    virtual inline void SetScale(const float& x, const float& y) { SetPosition(Vector2f(x, y)); }

    virtual inline float GetRotation() const = 0;
    virtual inline void SetRotation(const float& rot) = 0;

    virtual inline Color GetColor() const = 0;
    virtual inline void SetColor(const Color& color) = 0;

    virtual void Draw(GraphicsContext* pCtx) = 0;

};
}

#endif // DUSK_GRAPHICS_ACTOR_HPP
