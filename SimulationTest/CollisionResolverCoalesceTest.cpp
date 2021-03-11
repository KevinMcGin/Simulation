#include  <gtest/gtest.h>
#include "CollisionResolverCoalesce.h"
#include "ParticleSimple.h"

#include <vector>

TEST(CollisionResolverCoalesceTest, ParticlesCoalesce) {
	CollisionResolverCoalesce resolver;
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2 };
	resolver.resolve(p1, p2);
	EXPECT_EQ(1, particles.size());
	EXPECT_EQ(2, particles[0]->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, particles[0]->radius);
	EXPECT_EQ(Vector3D(1,0.5,0), particles[0]->position);
	EXPECT_EQ(Vector3D(1,0,0), particles[0]->velocity);
	EXPECT_EQ(Vector3D(0,0,0), particles[0]->angularVelocity);
}