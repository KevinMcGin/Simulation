#include  <gtest/gtest.h>
#include "ParticleDistributionSimple.h"
#include "DistributionGlobe.h"
#include "DistributionSimple.h"
#include "DistributionCircle.h"
#include "DistributionValue.h"
#include "DistributionMassDensity.h"


TEST(ParticleDistributionSimpleTest, ParticleMade) {
	auto massDistrubtion = make_shared<DistributionSimple>(0.1, 0.05);
	auto density = make_shared<DistributionValue>(1);
	auto densityDistribution = make_shared<DistributionMassDensity>(massDistrubtion, density);
	auto positionDistrubtion = make_shared<DistributionCircle>(Vector3D(0, 0, 0), 1);
	auto velocityDistrubtion = make_shared<DistributionCircle>(Vector3D(0, 0, 0), 0.005);
	auto angularVelocityDistrubtion = make_shared<DistributionCircle>(Vector3D(0, 0, 0), 0);
	ParticleDistributionSimple particleDistribution(densityDistribution, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
	Particle* p = particleDistribution.getParticle();
	EXPECT_TRUE(p->mass >= 0.05 && p->mass <= 0.15);
	EXPECT_TRUE(p->radius >= 0 && p->radius <= 0.5);
	EXPECT_TRUE(p->position.x <= 1 && p->position.x >= -1);
	EXPECT_TRUE(p->position.y <= 1 && p->position.y >= -1);
	EXPECT_TRUE(p->position.z <= 1 && p->position.z >= -1);
}