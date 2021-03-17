#include  <gtest/gtest.h>
#include "NewtonGravity.cuh"
#include "ParticleSimple.h"

#include <vector>

TEST(NewtonGravityTest, ParticlesAccelerate) {
	Law* law = new NewtonGravity(0.05);
	vector<Particle*> particles = { new ParticleSimple(1,1,{0,0.1,0},{0,0,0},{0,0,0}),  new ParticleSimple(100,1,{10,0,-0.03},{0,0,0},{0,0,0}) };
	law->run(particles);
	Vector3D velocity1 = particles.front()->velocity;
	Vector3D velocity2 = particles.back()->velocity;

	EXPECT_DOUBLE_EQ(0.04999182611370212, velocity1.x);
	EXPECT_DOUBLE_EQ(-0.00049991826113702121, velocity1.y);
	EXPECT_DOUBLE_EQ(-0.00014997547834110633, velocity1.z);
	EXPECT_DOUBLE_EQ(-0.00049991826113702121, velocity2.x);
	EXPECT_DOUBLE_EQ(0.0000049991826113702119, velocity2.y);
	EXPECT_DOUBLE_EQ(0.0000014997547834110634, velocity2.z);
}