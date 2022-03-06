#include  <gtest/gtest.h>
#include "law/newtonFirstLaw/NewtonFirstLaw.h"
#include "particle/ParticleSimple.h"
#include "NewtonFirstLawTestHelper.h"

#include <vector>

TEST(NewtonFirstLawTest, ParticleMove) {
	auto law = std::make_shared<NewtonFirstLaw>();
	std::vector<Particle*> particles = NewtonFirstLawTestHelper::getParticleMove();
	law->cpuLaw->run(particles);
	NewtonFirstLawTestHelper::testParticleMove(particles);
}