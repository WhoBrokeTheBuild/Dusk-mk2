#ifndef DUSK_GRAPHICS_CONTEXT_HPP
#define DUSK_GRAPHICS_CONTEXT_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>

#include <SFML/Graphics.hpp>

namespace dusk
{

class GraphicsSystem;
class Sprite;
class SpriteText;

class GraphicsContext : public TrackedObject
{

    friend class GraphicsSystem;

public:
    DUSK_CLASSNAME("Graphics Context")

    GraphicsContext() = delete;
    GraphicsContext(const GraphicsContext&) = delete;
    GraphicsContext& operator=(const GraphicsContext&) = delete;

    ~GraphicsContext() = default;
    
    void Clear();
    void SwapBuffers();

    void Draw(const sf::Drawable& drawable);
    void Draw(Sprite* sprite);
    void Draw(SpriteText* text);

    inline sf::RenderWindow& GetSFMLWindow() { return m_SfWindow; }

private:
    inline GraphicsContext(sf::RenderWindow& pSFMLWindow)
        : m_SfWindow(pSFMLWindow)
    {
    }

    sf::RenderWindow& m_SfWindow;

public:
    static void Script_RegisterFunctions();
    static int Script_Clear(lua_State* L);
    static int Script_Draw(lua_State* L);
    static int Script_SwapBuffers(lua_State* L);

}; // GraphicsContext

} // Dusk

#endif // DUSK_GRAPHICS_CONTEXT_HPP
