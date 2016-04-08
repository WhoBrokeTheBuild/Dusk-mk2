#include <gtest/gtest.h>
#include <Dusk/Graphics/Texture.hpp>

using namespace dusk;

TEST(Texture, LoadPNG) {
    Texture tex;
    ASSERT_TRUE(tex.Load("test.png"));
}

TEST(Texture, LoadJPEG) {
    Texture tex;
    ASSERT_TRUE(tex.Load("test.jpg"));
}

TEST(Texture, LoadTGA) {
    Texture tex;
    ASSERT_TRUE(tex.Load("test.tga"));
}

TEST(Texture, LoadBMP) {
    Texture tex;
    ASSERT_TRUE(tex.Load("test.bmp"));
}
