#include "cpp/distribution/SimulationInputDistributionStarSystem.h"
#include "cpp/distribution/DistributionValue.h"
#include "cpp/distribution/DistributionCircle.h"
#include "cpp/distribution/DistributionMassDensity.h"
#include "cpp/distribution/DistributionSimple.h"
#include "cpp/distribution/ParticleDistributionSimple.h"
#include "cpp/distribution/ParticleDistributionDisk.h"
#include "cpp/universe/input/SimulationInputRandomSimple.h"

SimulationInputDistributionStarSystem::SimulationInputDistributionStarSystem(
    StarSystemConfig config
) : config(config) {}

std::unique_ptr<SimulationInputRandomSimple> SimulationInputDistributionStarSystem::getStarSystemDistribution() {
    Vector3D<Real> meanPosition = { 0, 0, 0 };
	// The spreads arrive as fractions of the mean rather than absolute
	// amounts, so a disk stays as varied as it was when its mean mass or
	// density is changed by orders of magnitude.
	auto massDistribution = std::make_shared<DistributionSimple>(config.meanMass, config.meanMass * config.massSpread);
	auto density = std::make_shared<DistributionSimple>(config.meanDensity, config.meanDensity * config.densitySpread);
	auto densityDistribution = std::make_shared<DistributionMassDensity>(massDistribution, density);
	auto starDensity = std::make_shared<DistributionValue>(config.starDensity);
	auto distributionDensityStar = std::make_shared<DistributionMassDensity>(std::make_shared<DistributionValue>(config.starMass), starDensity);
	auto positionDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	auto velocityDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	// auto angularVelocityDistribution = std::make_shared<DistributionCircle>(Vector3D<Real>(0, 0, 0), 0);
	auto innerRadiusDistribution = std::make_shared<DistributionValue>(config.innerRadius);
	auto outerRadiusDistribution = std::make_shared<DistributionValue>(config.outerRadius);
	auto eccentricityDistribution = std::make_shared<DistributionValue>(1);
	auto particleDistributionDisk = std::make_shared<ParticleDistributionDisk>(
		densityDistribution,
		config.diskCentralMass,
		meanPosition,
		0,
		0,
		false,
		innerRadiusDistribution,
		outerRadiusDistribution,
		eccentricityDistribution/*, angularVelocityDistribution*/,
		config.positionBias
	);
	auto particleDistributionStar = std::make_shared<ParticleDistributionSimple>(distributionDensityStar, positionDistribution, velocityDistribution/*, angularVelocityDistribution*/);
	
	// particleCount is the whole system, star included, so the disk gets
	// one fewer. Counted rather than assumed: particleCount is unsigned, so
	// a system of none used to underflow to eighteen quintillion disk
	// particles — and a request for an empty star system is now an ordinary
	// thing to make, since the particles can be arriving as CSV instead.
	//
	// A massless star is a request for no star at all, which is how a disk
	// is seeded around something supplied separately.
	const bool hasStar = config.starMass > 0 && config.particleCount > 0;
	const unsigned long diskCount = config.particleCount - (hasStar ? 1 : 0);

	return std::make_unique<SimulationInputRandomSimple>(
		std::vector<unsigned long> { diskCount, hasStar ? 1UL : 0UL },
		std::vector<std::shared_ptr<ParticleDistribution>> { particleDistributionDisk, particleDistributionStar }		
	);
}
