#include  "gtest/gtest.h"
#include "shared/service/momentum/einstein/EinsteinMomentumService.cuh"


TEST(EinsteinMomentumServiceTest, getVelocityPlusAcceleration) {
	auto momentumService = EinsteinMomentumService();
	auto velocity = momentumService.getVelocityPlusAcceleration(
		1,
		{100000000, 1, 1}, 
		1,
		{100000000, 1, 1}
	);
	ASSERT_EQ(
		Vector3D<float>(173175104, 1.7317510843276978, 1.7317510843276978), 
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
	ASSERT_EQ(
		Vector3D<float>(261757904, 1.3087896108627319, 1.3087896108627319), 
		velocity
	);
}


TEST(EinsteinMomentumServiceTest, getMomentum) {
	class TestEinsteinMomentumService : public EinsteinMomentumService {
	public:
		Vector3D<float> getMomentum(float mass, Vector3D<float> velocity) {
			return EinsteinMomentumService::getMomentum(mass, velocity);
		}
	};
	auto momentumService = TestEinsteinMomentumService();
	auto momentum = momentumService.getMomentum(1, {100000000, 1, 1});
	ASSERT_EQ(
		Vector3D<float>(106075200, 1.0607520341873169, 1.0607520341873169), 
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
	ASSERT_EQ(
		Vector3D<float>(100000000, 1, 1), 
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
	ASSERT_EQ(
		Vector3D<float>(158832224, 1.0190718173980713, 1.0190718173980713), 
		v3
	);
}