#include  <gtest/gtest.h>
#include "ParticleDistributionSimple.h"
#include "DistributionGlobe.h"
#include "DistributionSimple.h"
#include "DistributionCircle.h"
#include "DistributionValue.h"
#include "DistributionMassDensity.h"


TEST(ParticleDistributionSimpleTest, ParticleMade) {
	Distribution* massDistrubtion = new DistributionSimple(0.1, 0.05);
	Distribution* density = new DistributionValue(1);
	DistributionDensity* densityDistribution = new DistributionMassDensity(massDistrubtion, density);
	Distribution3D* positionDistrubtion = new DistributionCircle({ 0,0,0 }, 1);
	Distribution3D* velocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0.005);
	Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
	ParticleDistributionSimple particleDistribution(densityDistribution, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
	Particle* p = particleDistribution.getParticle();
	EXPECT_TRUE(p->mass >= 0.05 && p->mass <= 0.15);
	EXPECT_TRUE(p->radius >= 0 && p->radius <= 0.5);
	EXPECT_TRUE(p->position.x <= 1 && p->position.x >= -1);
	EXPECT_TRUE(p->position.y <= 1 && p->position.y >= -1);
	EXPECT_TRUE(p->position.z <= 1 && p->position.z >= -1);
}