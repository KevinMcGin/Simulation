#include  <gtest/gtest.h>
#include "law/gravity/NewtonGravity.h"
#include "particle/ParticleSimple.h"
#include "NewtonGravityTestHelper.h"

#include <vector>

TEST(NewtonGravityTest, ParticlesAccelerate) {
	Law* law = new NewtonGravity(0.05);
	std::vector<Particle*> particles = NewtonGravityTestHelper::getParticlesAccelerate();
	law->cpuLaw->run(particles);
	NewtonGravityTestHelper::testParticlesAccelerate(particles);
}
