#include  "gtest/gtest.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"


TEST(NewtonMomentumServiceTest, getVelocityPlusAcceleration) {
	auto momentumService = NewtonMomentumService();
	auto velocity = momentumService.getVelocityPlusAcceleration(
		1,
		{100000000, 1, 1}, 
		1,
		{100000000, 1, 1}
	);
	ASSERT_EQ(
		Vector3D<Real>(200000000, 2, 2), 
		velocity
	);
}

TEST(NewtonMomentumServiceTest, getMomentum) {
	class TestNewtonMomentumService : public NewtonMomentumService {
	public:
		Vector3D<Real> getMomentum(Real mass, Vector3D<Real> velocity) {
			return NewtonMomentumService::getMomentum(mass, velocity);
		}
	};
	auto momentumService = TestNewtonMomentumService();
	auto momentum = momentumService.getMomentum(1, {100000000, 1, 1});
	ASSERT_EQ(
		Vector3D<Real>(100000000, 1, 1), 
		momentum
	);
}

TEST(NewtonMomentumServiceTest, mergeVelocitySame) {
	auto momentumService = NewtonMomentumService();
	auto v3 = momentumService.mergeVelocity(
		1, 
		{100000000, 1, 1},
		1, 
		{100000000, 1, 1}
	);
	ASSERT_EQ(
		Vector3D<Real>(100000000, 1, 1), 
		v3
	);
}

TEST(NewtonMomentumServiceTest, mergeVelocityDifferent) {
	auto momentumService = NewtonMomentumService();
	auto v3 = momentumService.mergeVelocity(
		1, 
		{100000000, 1, 1},
		1, 
		{200000000, 1, 1}
	);
	ASSERT_EQ(
		Vector3D<Real>(150000000, 1, 1), 
		v3
	);
}