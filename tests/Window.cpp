#include <gtest/gtest.h>
#include <Dusk/Graphics/GraphicsSystem.hpp>
#include <Dusk/Program.hpp>
#include <Dusk/Main.hpp>
#include <thread>
#include <chrono>

using namespace dusk;

class WindowTest :
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

TEST_F(WindowTest, Size) {
    //GraphicsSystem* pGS = Program::Inst()->GetGraphicsSystem();

    //pGS->SetWindowWidth(400);
    //pGS->ApplyWindowChanges();
    //ASSERT_EQ(400, pGS->GetWindowWidth());

    //pGS->SetWindowHeight(400);
    //pGS->ApplyWindowChanges();
    //ASSERT_EQ(400, pGS->GetWindowHeight());
}
