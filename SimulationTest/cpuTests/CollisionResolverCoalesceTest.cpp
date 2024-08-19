#include  <gtest/gtest.h>
#include "shared/law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "cpp/particle/ParticleSimple.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"

#include <vector>

TEST(CollisionResolverCoalesceTest, ParticlesCoalesce) {
	auto momentumService = std::make_shared<NewtonMomentumService>();
	CollisionResolverCoalesce resolver;
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 });
	resolver.resolve(p1, p2, momentumService.get());
	EXPECT_EQ(true, p2->deleted);
	EXPECT_EQ(2, p1->mass);
	EXPECT_FLOAT_EQ(1.2599210498948732, p1->radius);
	EXPECT_EQ(Vector3D<float>(2,0.5,0), p1->position);
	EXPECT_EQ(Vector3D<float>(1,0,0), p1->velocity);
}

TEST(CollisionResolverCoalesceTest, GetIndex) {
	CollisionResolverCoalesce resolver;
	int index = resolver.getIndex();
	EXPECT_EQ(0, index);
}