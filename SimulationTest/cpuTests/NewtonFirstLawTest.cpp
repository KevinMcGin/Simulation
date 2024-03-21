#include  <gtest/gtest.h>
#include "cpp/law/newtonFirstLaw/NewtonFirstLaw.h"
#include "cpp/particle/ParticleSimple.h"
#include "NewtonFirstLawTestHelper.h"

#include <vector>

TEST(NewtonFirstLawTest, ParticleMove) {
	auto law = std::make_shared<NewtonFirstLaw>();
	std::vector<Particle*> particles = NewtonFirstLawTestHelper::getParticleMove();
	law->cpuLaw->run(particles);
	NewtonFirstLawTestHelper::testParticleMove(particles);
}