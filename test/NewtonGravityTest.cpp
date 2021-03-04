#include "pch.h"
#include "../src/NewtonGravity.h"
#include "../src/ParticleSimple.h"

#include <vector>

TEST(NewtonGravityTest, ParticlesAccelerate) {
	Law* law = new NewtonGravity(0.5);
	vector<Particle*> particles = { new ParticleSimple(1,1,{0,0,0},{0,0,0},{0,0,0}),  new ParticleSimple(100,1,{10,0,0},{0,0,0},{0,0,0}) };
	law->run(particles);
	Vector3D velocity1 = particles.front()->velocity;
	Vector3D velocity2 = particles.back()->velocity;

	EXPECT_EQ(0.5, velocity1.x);
	EXPECT_EQ(0, velocity1.y);
	EXPECT_EQ(0, velocity1.z);
	EXPECT_EQ(-0.005, velocity2.x);
	EXPECT_EQ(0, velocity2.y);
	EXPECT_EQ(0, velocity2.z);
}