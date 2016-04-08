#include <gtest/gtest.h>
#include <Dusk/Scripting/ScriptHost.hpp>
#include <Dusk/Benchmark.hpp>
#include <Dusk/Program.hpp>
#include <Dusk/Main.hpp>
#include <thread>
#include <chrono>

using namespace dusk;

class TestProgram :
    public Program
{
public:

    TestProgram() :
        Program::Program()
    {
        SetHeadless(true);
    }

};

class ScriptingTest :
    public ::testing::Test
{
protected:

    void SetUp()
    {
        m_Thread = std::thread([](){
            ASSERT_EQ(0, DuskMain<TestProgram>(0, nullptr));
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
    Program::Inst()->GetScriptHost()->RunString(
        "dusk_log('info', 'Test print');\n"
        "DuskLog('info', 'Test print');\n"
    );
}
