#ifndef DUSK_GRAPHICS_FONT_HPP
#define DUSK_GRAPHICS_FONT_HPP

#include <Dusk/Config.hpp>
#include <Dusk/Tracking/TrackedObject.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Font.hpp>

namespace dusk
{

class SpriteText;

class Font : public TrackedObject
{

    friend class SpriteText;

public:
    DUSK_CLASSNAME("Font")

    Font() = default;
    Font(const Font&) = default;
    Font& operator=(const Font&) = default;
    virtual ~Font() = default;

    inline Font(const string& filename) { Load(filename); }

    bool Load(const string& filename);

    bool IsLoaded() const { return m_Loaded; }

private:
    inline const sf::Font& GetSFMLFont() const { return m_SfFont; }

    bool m_Loaded = false;

    string m_Filename;

    sf::Font m_SfFont;

public:
    static void Script_RegisterFunctions();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);

}; // class Font

} // namespace Dusk

#endif // DUSK_GRAPHICS_FONT_HPP
