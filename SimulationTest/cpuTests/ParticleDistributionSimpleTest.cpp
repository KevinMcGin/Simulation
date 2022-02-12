#include  <gtest/gtest.h>
#include "distribution/ParticleDistributionSimple.h"
#include "distribution/DistributionGlobe.h"
#include "distribution/DistributionSimple.h"
#include "distribution/DistributionCircle.h"
#include "distribution/DistributionValue.h"
#include "distribution/DistributionMassDensity.h"


TEST(ParticleDistributionSimpleTest, ParticleMade) {
	auto massDistrubtion = std::make_shared<DistributionSimple>(0.1, 0.05);
	auto density = std::make_shared<DistributionValue>(1);
	auto densityDistribution = std::make_shared<DistributionMassDensity>(massDistrubtion, density);
	auto positionDistrubtion = std::make_shared<DistributionCircle>(Vector3D(0, 0, 0), 1);
	auto velocityDistrubtion = std::make_shared<DistributionCircle>(Vector3D(0, 0, 0), 0.005);
	// auto angularVelocityDistrubtion = std::make_shared<DistributionCircle>(Vector3D(0, 0, 0), 0);
	ParticleDistributionSimple particleDistribution(densityDistribution, positionDistrubtion, velocityDistrubtion/*, angularVelocityDistrubtion*/);
	Particle* p = particleDistribution.getParticle();
	EXPECT_TRUE(p->mass >= 0.05 && p->mass <= 0.15);
	EXPECT_TRUE(p->radius >= 0 && p->radius <= 0.5);
	EXPECT_TRUE(p->position.x <= 1 && p->position.x >= -1);
	EXPECT_TRUE(p->position.y <= 1 && p->position.y >= -1);
	EXPECT_TRUE(p->position.z <= 1 && p->position.z >= -1);
}