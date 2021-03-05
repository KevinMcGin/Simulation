#include "pch.h"
#include "../src/CollisionResolverCoalesce.h"
#include "../src/ParticleSimple.h"

#include <vector>

TEST(CollisionResolverCoalesceTest, ParticlesCoalesce) {
	CollisionResolverCoalesce resolver;
	Particle* p1 = new ParticleSimple(1, 1, { 2,1,0 }, { 1,-1,0 }, { 0,0,0 });
	Particle* p2 = new ParticleSimple(1, 1, { 0,0,0 }, { 1,-1,0 }, { 0,0,0 });
	vector<Particle*> particles = { p1, p2 };
	resolver.resolve(p1, p2, particles);
	EXPECT_EQ(1, particles.size());
	EXPECT_EQ(2, p1->mass);
	EXPECT_DOUBLE_EQ(1.2599210498948732, p1->radius);
}