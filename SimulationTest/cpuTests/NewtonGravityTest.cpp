#include  <gtest/gtest.h>
#include "NewtonGravity.h"
#include "ParticleSimple.h"
#include "NewtonGravityTestHelper.h"

#include <vector>

TEST(NewtonGravityTest, ParticlesAccelerate) {
	Law* law = new NewtonGravity(0.05);
	vector<Particle*> particles = NewtonGravityTestHelper::getParticlesAccelerate();
	law->cpuLaw->run(particles);
	NewtonGravityTestHelper::testParticlesAccelerate(particles);
}
