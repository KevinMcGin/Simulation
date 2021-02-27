#include "pch.h"
#include "../src/NewtonGravity.h"
#include "../src/ParticleSimple.h"

#include <list>

TEST(NewtonGravityTest, ParticlesAccelerate) {
	Law* law = new NewtonGravity();
	list<Particle*> particles = { new ParticleSimple(1,1,{0,0,0},{0,0,0},{0,0,0}),  new ParticleSimple(100,1,{10,0,0},{0,0,0},{0,0,0}) };
	law->run(particles);
	array<double, 3> velocity1 = particles.front()->velocity;
	array<double, 3> velocity2 = particles.back()->velocity;

	EXPECT_EQ(0.5, velocity1[0]);
	EXPECT_EQ(0, velocity1[1]);
	EXPECT_EQ(0, velocity1[2]);
	EXPECT_EQ(-0.005, velocity2[0]);
	EXPECT_EQ(0, velocity2[1]);
	EXPECT_EQ(0, velocity2[2]);
}