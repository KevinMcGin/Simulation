#include "pch.h"
#include "../src/ParticleDistributionSimple.h"
#include "../src/DistributionGlobe.h"
#include "../src/DistributionSimple.h"
#include "../src/DistributionCircle.h"

TEST(ParticleDistributionSimpleTest, ParticleMade) {
	Distribution* massDistrubtion = new DistributionSimple(0.1, 0.05);
	Distribution* radiusDistrubtion = new DistributionSimple(0.01, 0.005);
	Distribution3D* positionDistrubtion = new DistributionCircle({ 0,0,0 }, 1);
	Distribution3D* velocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0.005);
	Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
	ParticleDistributionSimple particleDistribution(massDistrubtion, radiusDistrubtion, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
	Particle* p = particleDistribution.getParticle();
	EXPECT_TRUE(p->mass >= 0.05 && p->mass <= 0.15);
	EXPECT_TRUE(p->radius >= 0.005 && p->radius <= 0.015);
	EXPECT_TRUE(p->position.x <= 1 && p->position.x >= -1);
	EXPECT_TRUE(p->position.y <= 1 && p->position.y >= -1);
	EXPECT_TRUE(p->position.z <= 1 && p->position.z >= -1);
}