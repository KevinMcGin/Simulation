#include  <gtest/gtest.h>
#include "NewtonFirstLaw.cuh"
#include "ParticleSimple.h"

#include <vector>

TEST(NewtonFirstLawTest, ParticleMove) {
	Law* law = new NewtonFirstLaw();
	vector<Particle*> particles = { new ParticleSimple(1,1,{0,0,0},{1,-1,0},{0,0,0}) };
	law->run(particles);
	Vector3D positions = particles.front()->position;
	EXPECT_EQ(1, positions.x);
	EXPECT_EQ(-1, positions.y);
	EXPECT_EQ(0, positions.z);
}