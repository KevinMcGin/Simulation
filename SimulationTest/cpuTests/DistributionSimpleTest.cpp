#include  <gtest/gtest.h>
#include "distribution/DistributionSimple.h"

TEST(DistributionSimpleTest, DistributionSimpleTest) {
	DistributionSimple distribution(2, 1);
	float value = distribution.getValue();
	EXPECT_TRUE(value >= 1 && value <= 3);
}

