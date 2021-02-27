#include "pch.h"
#include "../src/NewtonFirstLaw.h"
#include "../src/ParticleSimple.h"

#include <list>

TEST(NewtonFirstLawTest, ParticleMove) {
	Law* law = new NewtonFirstLaw();
	list<Particle*> particles = { new ParticleSimple(1,1,{0,0,0},{1,-1,0},{0,0,0}) };
	law->run(particles);
	array<double, 3> positions = particles.front()->position;
	EXPECT_EQ(1, positions[0]);
	EXPECT_EQ(-1, positions[1]);
	EXPECT_EQ(0, positions[2]);
}