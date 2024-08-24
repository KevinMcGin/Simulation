#include  <gtest/gtest.h>
#include "cpp/law/gravity/NewtonGravity.h"
#include "cpp/particle/ParticleSimple.h"
#include "NewtonGravityTestHelper.h"
#include "shared/service/momentum/newton/NewtonMomentumService.cuh"

#include <vector>

TEST(NewtonGravityTest, ParticlesAccelerate) {
	auto momentumService = std::make_shared<NewtonMomentumService>();
	auto law = std::make_shared<NewtonGravity>(momentumService, 0.05);
	std::vector<Particle*> particles = NewtonGravityTestHelper::getParticlesAccelerate();
	law->cpuLaw->run(particles);
	NewtonGravityTestHelper::testParticlesAccelerate(particles);
}
