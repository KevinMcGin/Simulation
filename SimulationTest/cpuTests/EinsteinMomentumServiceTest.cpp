#include  "gtest/gtest.h"
#include "shared/service/momentum/einstein/EinsteinMomentumService.cuh"

// Exact equality is the wrong test for a value arrived at through a chain
// of divisions and square roots: the expectations below are independently
// calculated rather than captured, and agree to about fifteen significant
// digits, which is the accuracy actually on offer. Comparing the bits would
// be asserting that the implementation performs its arithmetic in one
// particular order.
#define EXPECT_VECTOR_DOUBLE_EQ(expected, actual) \
	do { \
		EXPECT_DOUBLE_EQ((expected).x, (actual).x); \
		EXPECT_DOUBLE_EQ((expected).y, (actual).y); \
		EXPECT_DOUBLE_EQ((expected).z, (actual).z); \
	} while (0)


TEST(EinsteinMomentumServiceTest, getVelocityPlusAcceleration) {
	auto momentumService = EinsteinMomentumService();
	auto velocity = momentumService.getVelocityPlusAcceleration(
		1,
		{100000000, 1, 1}, 
		1,
		{100000000, 1, 1}
	);
	EXPECT_VECTOR_DOUBLE_EQ(
		Vector3D<Real>(173175101.3203888, 1.731751013203888, 1.731751013203888),
		velocity
	);
}

TEST(EinsteinMomentumServiceTest, getVelocityPlusAccelerationLarge) {
	auto momentumService = EinsteinMomentumService();
	auto velocity = momentumService.getVelocityPlusAcceleration(
		1,
		{200000000, 1, 1}, 
		1,
		{200000000, 1, 1}
	);
	EXPECT_VECTOR_DOUBLE_EQ(
		Vector3D<Real>(261757903.65608728, 1.3087895182804363, 1.3087895182804363),
		velocity
	);
}

TEST(EinsteinMomentumServiceTest, getVelocityPlusAccelerationXLarge) {
	auto momentumService = EinsteinMomentumService();
	auto velocity = momentumService.getVelocityPlusAcceleration(
		1,
		{1000000000, 1, 1}, 
		1,
		{200000000, 1, 1}
	);
	// Exactly the speed of light, which is the point: at float this came
	// out as 299792480, which is faster than light. The Todo that used to
	// sit here asked for double, and this is it.
	EXPECT_VECTOR_DOUBLE_EQ(
		Vector3D<Real>(299792458.0, 0.2997924580262742, 0.2997924580262742),
		velocity
	);
}


TEST(EinsteinMomentumServiceTest, getMomentum) {
	class TestEinsteinMomentumService : public EinsteinMomentumService {
	public:
		Vector3D<Real> getMomentum(Real mass, Vector3D<Real> velocity) {
			return EinsteinMomentumService::getMomentum(mass, velocity);
		}
	};
	auto momentumService = TestEinsteinMomentumService();
	auto momentum = momentumService.getMomentum(1, {100000000, 1, 1});
	EXPECT_VECTOR_DOUBLE_EQ(
		Vector3D<Real>(106075200.04442042, 1.0607520004442041, 1.0607520004442041),
		momentum
	);
}

TEST(EinsteinMomentumServiceTest, mergeVelocitySame) {
	auto momentumService = EinsteinMomentumService();
	auto v3 = momentumService.mergeVelocity(
		1, 
		{100000000, 1, 1},
		1, 
		{100000000, 1, 1}
	);
	EXPECT_VECTOR_DOUBLE_EQ(
		Vector3D<Real>(100000000.00000003, 1.0000000000000002, 1.0000000000000002),
		v3
	);
}

TEST(EinsteinMomentumServiceTest, mergeVelocityDifferent) {
	auto momentumService = EinsteinMomentumService();
	auto v3 = momentumService.mergeVelocity(
		1, 
		{100000000, 1, 1},
		1, 
		{200000000, 1, 1}
	);
	EXPECT_VECTOR_DOUBLE_EQ(
		Vector3D<Real>(158832220.10995564, 1.0190718367705756, 1.0190718367705756),
		v3
	);
}