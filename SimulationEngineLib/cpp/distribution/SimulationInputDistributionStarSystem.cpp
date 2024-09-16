#include "cpp/distribution/SimulationInputDistributionStarSystem.h"
#include "cpp/distribution/DistributionValue.h"
#include "cpp/distribution/DistributionCircle.h"
#include "cpp/distribution/DistributionMassDensity.h"
#include "cpp/distribution/ParticleDistributionSimple.h"
#include "cpp/distribution/ParticleDistributionDisk.h"
#include "cpp/universe/input/SimulationInputRandomSimple.h"

SimulationInputDistributionStarSystem::SimulationInputDistributionStarSystem(
    float meanMass,
    float meanDensity,
    float starMass,
    float outerRadius,
    unsigned long particleCount
) : meanMass(meanMass), 
    meanDensity(meanDensity), 
    starMass(starMass), 
    outerRadius(outerRadius), 
    particleCount(particleCount) {}

std::unique_ptr<SimulationInputRandomSimple> SimulationInputDistributionStarSystem::getStarSystemDistribution() {
    Vector3D<float> meanPosition = { 0, 0, 0 };
	auto massDistribution = std::make_shared<DistributionSimple>(meanMass, meanMass*0.9);
	auto density = std::make_shared<DistributionValue>(meanDensity);
	auto densityDistribution = std::make_shared<DistributionMassDensity>(massDistribution, density);
	auto distributionDensityStar = std::make_shared<DistributionMassDensity>(std::make_shared<DistributionValue>(starMass), density);
	auto positionDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	auto velocityDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	// auto angularVelocityDistribution = std::make_shared<DistributionCircle>(Vector3D<float>(0, 0, 0), 0);
	auto innerRadiusDistribution = std::make_shared<DistributionValue>(0.5f);
	auto outerRadiusDistribution = std::make_shared<DistributionValue>(outerRadius);
	auto eccentricityDistribution = std::make_shared<DistributionValue>(1);
	auto particleDistributionDisk = std::make_shared<ParticleDistributionDisk>(densityDistribution, starMass, meanPosition, 0, 0, false, innerRadiusDistribution, outerRadiusDistribution, eccentricityDistribution/*, angularVelocityDistribution*/);	
	auto particleDistributionStar = std::make_shared<ParticleDistributionSimple>(distributionDensityStar, positionDistribution, velocityDistribution/*, angularVelocityDistribution*/);
	
	return std::make_unique<SimulationInputRandomSimple>(
		std::vector<unsigned long> { particleCount - 1, 1 }, 
		std::vector<std::shared_ptr<ParticleDistribution>> { particleDistributionDisk, particleDistributionStar }		
	);
}