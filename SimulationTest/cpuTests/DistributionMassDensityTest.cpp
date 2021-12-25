#include  <gtest/gtest.h>
#include "DistributionMassDensity.h"
#include "DistributionValue.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>

TEST(DistributionMassDensityTest, GetsMassRadius) {
	auto massDistribution = std::make_shared<DistributionValue>(10);
	auto densityDistribution = std::make_shared<DistributionValue>(1);
	DistributionMassDensity distrubtion(massDistribution, densityDistribution);

	double mass, radius;
	distrubtion.getMassRadius(mass, radius);
	EXPECT_EQ(10, mass);
	EXPECT_DOUBLE_EQ(1.336504617571975, radius);
}