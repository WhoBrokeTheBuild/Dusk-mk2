#include "GraphicsSystem.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Graphics/Texture.hpp>
#include <Dusk/Graphics/Sprite.hpp>
#include <Dusk/Benchmark.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Input/InputSystem.hpp>

#include <SFML/Window/Event.hpp>

namespace dusk
{

bool
GraphicsSystem::CreateWindow()
{
    DuskBenchStart();

    CreateSFMLWindow();
    mp_GraphicsContext.reset(New GraphicsContext(m_SfWindow));

    Program::Inst()->AddEventListener(Program::EvtUpdate, this, &GraphicsSystem::OnUpdate);

    DuskBenchEnd("GraphicsSystem::CreateWindow");
    return true;
}

void
GraphicsSystem::OnUpdate(const Event& event)
{
    InputSystem* pIS = Program::Inst()->GetInputSystem();

    sf::Event sfEvent;
    while (m_SfWindow.pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed)
        {
            m_SfWindow.close();
            Program::Inst()->Exit();
        }
        else if (sfEvent.type == sf::Event::Resized)
        {
            m_Width = sfEvent.size.width;
            m_Height = sfEvent.size.height;

            Dispatch(Event(EvtWindowResize, WindowResizeEventData(m_Width, m_Height)));
        }
        else
        {
            pIS->ProcessSfEvent(sfEvent);
        }
    }
}

Vector2u
GraphicsSystem::GetWindowSize() const
{
    return m_SfWindow.getSize();
}

void
GraphicsSystem::SetWindowWidth(const unsigned int& width)
{
    m_Width = width;
}

void
GraphicsSystem::SetWindowHeight(const unsigned int& height)
{
    m_Height = height;
}

void
GraphicsSystem::SetWindowSize(const unsigned int& width, const unsigned int& height)
{
    m_Width = width;
    m_Height = height;
}

void
GraphicsSystem::SetWindowStyle(const int& styleFlags)
{
    m_Style = styleFlags;
}

void
GraphicsSystem::ApplyWindowChanges()
{
    CreateSFMLWindow();
    Dispatch(Event(EvtWindowResize, WindowResizeEventData(m_Width, m_Height)));
}

void
GraphicsSystem::SetWindowTitle(const string& title)
{
    m_Title = title;
    m_SfWindow.setTitle(title);
}

bool
GraphicsSystem::IsFullscreen() const
{
    return (m_Style & WindowStyle::Fullscreen) > 0;
}

bool
GraphicsSystem::IsDecorated() const
{
    return (m_Style & WindowStyle::Decorated) > 0;
}

bool
GraphicsSystem::IsResizable() const
{
    return (m_Style & WindowStyle::Resizable) > 0;
}

GraphicsContext*
GraphicsSystem::GetContext() const
{
    return mp_GraphicsContext.get();
}

bool
GraphicsSystem::CreateSFMLWindow()
{
    uint32_t style = 0;

    if (IsFullscreen())
    {
        style = sf::Style::Fullscreen;
    }
    else
    {
        style |= sf::Style::Close;

        if (IsResizable())
            style |= sf::Style::Resize;

        if (IsDecorated())
            style |= sf::Style::Titlebar;
    }

    m_SfWindow.create(sf::VideoMode(m_Width, m_Height), m_Title, style);

    m_SfWindow.setKeyRepeatEnabled(false);

    Vector2u actualSize = m_SfWindow.getSize();
    m_Width = actualSize.x;
    m_Height = actualSize.y;

    return m_SfWindow.isOpen();
}

void
GraphicsSystem::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_get_graphics_system", &GraphicsSystem::Script_Get);
    Scripting::RegisterFunction(
        "dusk_graphics_system_get_context", &GraphicsSystem::Script_GetContext);
    Scripting::RegisterFunction(
        "dusk_graphics_system_get_window_size", &GraphicsSystem::Script_GetWindowSize);
    Scripting::RegisterFunction(
        "dusk_graphics_system_get_window_title", &GraphicsSystem::Script_GetWindowTitle);
    Scripting::RegisterFunction(
        "dusk_graphics_system_set_window_title", &GraphicsSystem::Script_SetWindowTitle);

    GraphicsContext::Script_RegisterFunctions();
    Texture::Script_RegisterFunctions();
    Sprite::Script_RegisterFunctions();
}

int
GraphicsSystem::Script_Get(lua_State* L)
{
    lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem());
    return 1;
}

int
GraphicsSystem::Script_GetContext(lua_State* L)
{
    lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetContext());
    return 1;
}

int
GraphicsSystem::Script_GetWindowSize(lua_State* L)
{
    GraphicsSystem* pGS = Program::Inst()->GetGraphicsSystem();
    Vector2u size = pGS->GetWindowSize();
    lua_pushinteger(L, size.x);
    lua_pushinteger(L, size.y);
    return 2;
}

int
GraphicsSystem::Script_GetWindowTitle(lua_State* L)
{
    GraphicsSystem* pGS = Program::Inst()->GetGraphicsSystem();
    string title = pGS->GetWindowTitle();
    lua_pushstring(L, title.c_str());
    return 1;
}

int
GraphicsSystem::Script_SetWindowTitle(lua_State* L)
{
    GraphicsSystem* pGS = Program::Inst()->GetGraphicsSystem();
    string title = lua_tostring(L, 1);
    pGS->SetWindowTitle(title);
    return 0;
}

int
WindowResizeEventData::PushDataToLua(lua_State* L) const
{
    lua_pushinteger(L, m_Width);
    lua_pushinteger(L, m_Height);
    return 2;
}

} // namespace dusk
