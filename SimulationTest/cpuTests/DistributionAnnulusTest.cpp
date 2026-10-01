#include <gtest/gtest.h>
#include "cpp/distribution/DistributionAnnulus.h"
#include <cmath>

namespace {
	// The mean radius of a sample, which is what a bias moves: the ring and
	// its bounds stay the same, only where in it the points gather changes.
	Real meanRadius(DistributionAnnulus& annulus, unsigned int samples) {
		Real total = 0;
		for (unsigned int i = 0; i < samples; i++) {
			total += annulus.getValue().magnitude();
		}
		return total / (Real)samples;
	}
}

TEST(DistributionAnnulusTest, staysBetweenTheRadii) {
	DistributionAnnulus annulus(Vector3D<Real>(0, 0, 0), 2, 5);

	for (unsigned int i = 0; i < 200; i++) {
		auto value = annulus.getValue();
		EXPECT_GE(value.magnitude(), 1.99);
		EXPECT_LE(value.magnitude(), 5.01);
		EXPECT_DOUBLE_EQ(0, value.z) << "the disk is flat";
	}
}

TEST(DistributionAnnulusTest, isOffsetByItsMean) {
	DistributionAnnulus annulus(Vector3D<Real>(10, 0, 0), 0, 1);

	for (unsigned int i = 0; i < 200; i++) {
		auto value = annulus.getValue();
		EXPECT_GE(value.x, 8.99);
		EXPECT_LE(value.x, 11.01);
	}
}

// A ring of no width is the one point every sample has to land on, rather
// than a range to draw from.
TEST(DistributionAnnulusTest, handlesAZeroWidthRing) {
	DistributionAnnulus annulus(Vector3D<Real>(0, 0, 0), 0, 0);

	EXPECT_DOUBLE_EQ(0, annulus.getValue().magnitude());
}

// An inner radius past the outer one describes no ring at all. It collapses
// onto the outer radius instead of looping forever looking for a point that
// satisfies both.
TEST(DistributionAnnulusTest, clampsAnInnerRadiusPastTheOuterOne) {
	DistributionAnnulus annulus(Vector3D<Real>(0, 0, 0), 9, 3);

	EXPECT_NEAR(3, annulus.getValue().magnitude(), 0.01);
}

TEST(DistributionAnnulusTest, biasOfAHalfLeavesTheSampleEven) {
	EXPECT_DOUBLE_EQ(1, DistributionAnnulus::biasExponent(0.5));

	DistributionAnnulus annulus(Vector3D<Real>(0, 0, 0), 0, 10);
	// An even spread over 0..10 averages 5; the tolerance is the sampling
	// error of 2,000 draws, not a claim about the shape.
	EXPECT_NEAR(5.0, meanRadius(annulus, 2000), 0.5);
}

TEST(DistributionAnnulusTest, biasMovesTheSampleTowardsAnEdge) {
	DistributionAnnulus inner(Vector3D<Real>(0, 0, 0), 0, 10, 0.2);
	DistributionAnnulus even(Vector3D<Real>(0, 0, 0), 0, 10, 0.5);
	DistributionAnnulus outer(Vector3D<Real>(0, 0, 0), 0, 10, 0.8);

	const Real innerMean = meanRadius(inner, 2000);
	const Real evenMean = meanRadius(even, 2000);
	const Real outerMean = meanRadius(outer, 2000);

	EXPECT_LT(innerMean, evenMean);
	EXPECT_LT(evenMean, outerMean);
}

// The ends are included, and are the ring collapsing to a single circle
// rather than a bias towards one of its edges.
TEST(DistributionAnnulusTest, aBiasOfZeroPutsEverythingOnTheInnerRadius) {
	EXPECT_TRUE(std::isinf(DistributionAnnulus::biasExponent(0)));

	DistributionAnnulus annulus(Vector3D<Real>(0, 0, 0), 1, 4, 0);
	for (unsigned int i = 0; i < 200; i++) {
		EXPECT_NEAR(1, annulus.getValue().magnitude(), 0.01);
	}
}

TEST(DistributionAnnulusTest, aBiasOfOnePutsEverythingOnTheOuterRadius) {
	EXPECT_DOUBLE_EQ(0, DistributionAnnulus::biasExponent(1));

	DistributionAnnulus annulus(Vector3D<Real>(0, 0, 0), 1, 4, 1);
	for (unsigned int i = 0; i < 200; i++) {
		EXPECT_NEAR(4, annulus.getValue().magnitude(), 0.01);
	}
}

// Only a bias outside 0..1 is corrected, since there is nothing between the
// ends left to interpret it as.
TEST(DistributionAnnulusTest, clampsABiasOutsideItsRange) {
	EXPECT_DOUBLE_EQ(DistributionAnnulus::biasExponent(1), DistributionAnnulus::biasExponent(4));
	EXPECT_TRUE(std::isinf(DistributionAnnulus::biasExponent(-1)));
}
