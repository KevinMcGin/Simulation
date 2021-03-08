#include "pch.h"
#include "../src/NewtonGravity.h"
#include "../src/ParticleSimple.h"

#include <vector>

TEST(NewtonGravityTest, ParticlesAccelerate) {
	Law* law = new NewtonGravity(0.05);
	vector<Particle*> particles = { new ParticleSimple(1,1,{0,0.1,0},{0,0,0},{0,0,0}),  new ParticleSimple(100,1,{10,0,-0.03},{0,0,0},{0,0,0}) };
	law->run(particles);
	Vector3D velocity1 = particles.front()->velocity;
	Vector3D velocity2 = particles.back()->velocity;

	EXPECT_DOUBLE_EQ(0.049997275222748515, velocity1.x);
	EXPECT_DOUBLE_EQ(-4.9997275222748518, velocity1.y);
	EXPECT_DOUBLE_EQ(-16.665758407582842, velocity1.z);
	EXPECT_DOUBLE_EQ(-0.00049997275222748517, velocity2.x);
	EXPECT_DOUBLE_EQ(0.049997275222748515, velocity2.y);
	EXPECT_DOUBLE_EQ(0.16665758407582842, velocity2.z);
}