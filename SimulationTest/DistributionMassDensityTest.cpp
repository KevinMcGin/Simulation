#include "pch.h"
#include "../src/DistributionMassDensity.h"
#include "../src/DistributionValue.h"
#define _USE_MATH_DEFINES
#include <math.h>

TEST(DistributionMassDensityTest, GetsMassRadius) {
	Distribution* massDistribution = new DistributionValue(10);
	Distribution* densityDistribution = new DistributionValue(1);
	DistributionMassDensity distrubtion(massDistribution, densityDistribution);

	double mass, radius;
	distrubtion.getMassRadius(mass, radius);
	EXPECT_EQ(10, mass);
	EXPECT_DOUBLE_EQ(1.336504617571975, radius);
}