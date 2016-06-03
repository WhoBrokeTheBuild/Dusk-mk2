#ifndef EXAMPLE_PROGRAM_HPP
#define EXAMPLE_PROGRAM_HPP

#include <memory>
#include <Dusk/Config.hpp>
#include <Dusk/Program.hpp>
#include <Dusk/Graphics/SpriteText.hpp>
#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Timing/FrameTimeInfo.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>

using namespace std;
using namespace dusk;

class ExampleProgram : public Program
{
public:
    ExampleProgram(const ExampleProgram&) = delete;
    ExampleProgram& operator=(const ExampleProgram&) = delete;
    ExampleProgram();
    ~ExampleProgram();

    void Update(FrameTimeInfo& time) override;
    void Render(GraphicsContext* ctx) override;

    void OnKeyPress(const Event& evt);

private:
    unique_ptr<Font> mp_Font;
    unique_ptr<SpriteText> mp_Text;

    float m_TextSpeed = 5.0f;
    Vector2f m_TextVel;
};

#endif // EXAMPLE_PROGRAM_HPP
