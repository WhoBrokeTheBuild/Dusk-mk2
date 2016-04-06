#include <gtest/gtest.h>
#include <Dusk/Scripting/ScriptHost.hpp>
#include <Dusk/Program.hpp>
#include <Dusk/Main.hpp>
#include <thread>
#include <chrono>

using namespace dusk;

class ScriptingTest :
    public ::testing::Test
{
protected:

    void SetUp()
    {
        m_Thread = std::thread([](){
            ASSERT_EQ(0, DuskMain<Program>(0, nullptr));
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void TearDown()
    {
        Program::Inst()->Exit();
        m_Thread.join();
    }

    std::thread m_Thread;
};

TEST_F(ScriptingTest, Print) {
    Program::Inst()->GetScriptHost()->RunString("print 'Hello, World!';");
}
