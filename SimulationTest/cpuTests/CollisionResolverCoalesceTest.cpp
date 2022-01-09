#include  <gtest/gtest.h>
#include "law/collision/resolver/CollisionResolverCoalesce.cuh"
#include "particle/ParticleSimple.h"

#include <vector>

TEST(CollisionResolverCoalesceTest, ParticlesCoalesce) {
	CollisionResolverCoalesce resolver;
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 2,0,0 }, { 1,1,0 }, { 0,0,0 });
	resolver.resolve(p1, p2);
	EXPECT_EQ(true, p2->deleted);
	EXPECT_EQ(2, p1->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, p1->radius);
	EXPECT_EQ(Vector3D(2,0.5,0), p1->position);
	EXPECT_EQ(Vector3D(1,0,0), p1->velocity);
	EXPECT_EQ(Vector3D(0,0,0), p1->angularVelocity);
}