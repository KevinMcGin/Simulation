#include  <gtest/gtest.h>
#include "NewtonFirstLaw.cuh"
#include "ParticleSimple.h"
#include "NewtonFirstLawTestHelper.h"

#include <vector>

TEST(NewtonFirstLawTest, ParticleMove) {
	Law* law = new NewtonFirstLaw();
	vector<Particle*> particles = NewtonFirstLawTestHelper::getParticleMove();
	law->cpuRun(particles);
	NewtonFirstLawTestHelper::testParticleMove(particles);
}