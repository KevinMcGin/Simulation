#include  <gtest/gtest.h>
#include "cpp/distribution/ParticleDistributionDisk.h"
#include "cpp/distribution/DistributionValue.h"
#include "cpp/distribution/DistributionMassDensity.h"
#include "cpp/distribution/DistributionCircle.h"
#include "cpp/distribution/DistributionSimple.h"

#include <memory>

TEST(ParticleDistributionDiskTest, Disk) {
    Vector3D<Real> meanPosition(0, 0, 0);
    Real starMass = 1;
    Real meanDensity = 1;
    Real outerRadius = 1;
    Real meanMass = 1;
    auto starMassDistribution = std::make_shared<DistributionValue>(starMass);
	auto massDistribution = std::make_shared<DistributionValue>(meanMass);
	auto density = std::make_shared<DistributionValue>(meanDensity);
    auto densityDistribution = std::make_shared<DistributionMassDensity>(massDistribution, density);
	auto distributionDensityStar = std::make_shared<DistributionMassDensity>(starMassDistribution, density);
	auto positionDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	auto velocityDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	// auto angularVelocityDistribution = std::make_shared<DistributionCircle>(Vector3D<Real>(0, 0, 0), 0);
	auto innerRadiusDistribution = std::make_shared<DistributionValue>(0);
	auto outerRadiusDistribution = std::make_shared<DistributionValue>(outerRadius);
	auto eccentricityDistribution = std::make_shared<DistributionValue>(1);
	ParticleDistributionDisk particleDistributionDisk(
        densityDistribution, 
        starMass, 
        meanPosition, 
        0, 
        0, 
        true, 
        innerRadiusDistribution, 
        outerRadiusDistribution, 
        eccentricityDistribution//, 
        // angularVelocityDistribution
    );
    auto particle = particleDistributionDisk.getParticle();
	EXPECT_DOUBLE_EQ(1, particle->mass);
	EXPECT_TRUE(particle->radius >= 0 && particle->radius <= 1);
	EXPECT_TRUE(particle->position.x >= -1 && particle->position.x <= 1);
	EXPECT_TRUE(particle->position.y >= -1 && particle->position.y <= 1);
	EXPECT_TRUE(particle->position.z >= 0 && particle->position.z <= 0);
	EXPECT_TRUE(particle->velocity.x >= -1 && particle->velocity.x <= 1);
	EXPECT_TRUE(particle->velocity.y >= -1 && particle->velocity.y <= 1);
	EXPECT_TRUE(particle->velocity.z >= 0 && particle->velocity.z <= 0);
	delete particle;
}

TEST(ParticleDistributionDiskTest, DiskZeroRadius) {
    Vector3D<Real> meanPosition(0, 0, 0);
    Real starMass = 1;
    Real meanDensity = 1;
    Real outerRadius = 0;
    Real meanMass = 1;
    auto starMassDistribution = std::make_shared<DistributionValue>(starMass);
	auto massDistribution = std::make_shared<DistributionValue>(meanMass);
	auto density = std::make_shared<DistributionValue>(meanDensity);
    auto densityDistribution = std::make_shared<DistributionMassDensity>(massDistribution, density);
	auto distributionDensityStar = std::make_shared<DistributionMassDensity>(starMassDistribution, density);
	auto positionDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	auto velocityDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	// auto angularVelocityDistribution = std::make_shared<DistributionCircle>(Vector3D<Real>(0, 0, 0), 0);
	auto innerRadiusDistribution = std::make_shared<DistributionValue>(0);
	auto outerRadiusDistribution = std::make_shared<DistributionValue>(outerRadius);
	auto eccentricityDistribution = std::make_shared<DistributionValue>(1);
	ParticleDistributionDisk particleDistributionDisk(
        densityDistribution, 
        starMass, 
        meanPosition, 
        0, 
        0, 
        true, 
        innerRadiusDistribution, 
        outerRadiusDistribution, 
        eccentricityDistribution//, 
        // angularVelocityDistribution
    );
    auto particle = particleDistributionDisk.getParticle();
	EXPECT_DOUBLE_EQ(1, particle->mass);
	EXPECT_TRUE(particle->radius >= 0 && particle->radius <= 1);
	EXPECT_TRUE(particle->position.x >= -1 && particle->position.x <= 1);
	EXPECT_TRUE(particle->position.y >= -1 && particle->position.y <= 1);
	EXPECT_TRUE(particle->position.z >= 0 && particle->position.z <= 0);
	EXPECT_TRUE(particle->velocity.x >= -1 && particle->velocity.x <= 1);
	EXPECT_TRUE(particle->velocity.y >= -1 && particle->velocity.y <= 1);
	EXPECT_TRUE(particle->velocity.z >= 0 && particle->velocity.z <= 0);
	delete particle;
}
