#include <gtest/gtest.h>
#include <Dusk/Strings.hpp>

using namespace dusk;

TEST(Strings, Basename) {
	EXPECT_EQ(Basename("/path/to/filename"), "filename");
	EXPECT_EQ(Basename("path/to/filename"), "filename");
	EXPECT_EQ(Basename("/path/to/filename.txt"), "filename.txt");
	EXPECT_EQ(Basename("path/to/filename.txt"), "filename.txt");
}

TEST(Strings, Dirname) {
	EXPECT_EQ(Dirname("/path/to/filename"), "/path/to");
	EXPECT_EQ(Dirname("path/to/filename"), "path/to");
	EXPECT_EQ(Dirname("/path/to/filename.txt"), "/path/to");
	EXPECT_EQ(Dirname("path/to/filename.txt"), "path/to");
}
