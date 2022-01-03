#include  <gtest/gtest.h>
#include "Distribution.h"

TEST(DistributionTest, RandomTest) {
	auto value = Distribution::random(0.0, 1.0);
	EXPECT_TRUE(value <= 1 && value >= -1);
}
TEST(DistributionTest, RandomTest2) {
	auto value = Distribution::random(1.0);
	EXPECT_TRUE(value <= 1 && value >= 0);
}
