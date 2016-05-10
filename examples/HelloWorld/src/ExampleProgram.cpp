#include "ExampleProgram.hpp"

ExampleProgram::ExampleProgram()
    : mp_Font(New Font("data/Roboto.ttf"))
    , mp_Text(New SpriteText(mp_Font.get(), "Hello, World", 48, Color::White))
{
    mp_Text->SetPosition(Vector2f(0, 0));
    m_TextVel = Vector2f(m_TextSpeed, m_TextSpeed);
}

void
ExampleProgram::Update(FrameTimeInfo& time)
{
    Program::Update(time);

    Vector2u winSize = GetGraphicsSystem()->GetWindowSize();
    Vector2f textPos = mp_Text->GetPosition();
    Vector2f textSize = mp_Text->GetSize();

    if (textPos.x < 0)
    {
        m_TextVel.x = m_TextSpeed;
    }
    else if (textPos.x + textSize.x > winSize.x)
    {
        m_TextVel.x = -m_TextSpeed;
    }

    if (textPos.y < 0)
    {
        m_TextVel.y = m_TextSpeed;
    }
    else if (textPos.y + textSize.y > winSize.y)
    {
        m_TextVel.y = -m_TextSpeed;
    }

    mp_Text->SetPosition(mp_Text->GetPosition() +
                         Vector2f(m_TextVel.x * time.Delta, m_TextVel.y * time.Delta));
}

void
ExampleProgram::Render(GraphicsContext *ctx)
{
    Program::Render(ctx);
    
    ctx->Draw(mp_Text.get());
}
