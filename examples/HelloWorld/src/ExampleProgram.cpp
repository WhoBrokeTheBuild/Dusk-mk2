#include "ExampleProgram.hpp"

ExampleProgram::ExampleProgram()
    : mp_Font(New Font("data/Roboto.ttf"))
    , mp_Text(New SpriteText(mp_Font.get(), "Hello, World", 48, Color::White))
{
    mp_Text->SetPosition(Vector2f(40, 40));
}

void
ExampleProgram::Render(GraphicsContext *ctx)
{
    ctx->Draw(mp_Text.get());
}
