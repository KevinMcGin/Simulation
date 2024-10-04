#include  "gtest/gtest.h"
#include "cpp/util/FileUtil.h"
#include <fstream>

TEST(FileUtilTest, fileToString) {
	std::string expected = "Test string";

	std::ofstream file("test.txt");
	file << expected;
	file.close();

	std::string actual = FileUtil::fileToString("test.txt");
	EXPECT_STREQ(expected.c_str(), actual.c_str());
}