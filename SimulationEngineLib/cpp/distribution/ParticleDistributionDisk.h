#pragma once
#include "shared/precision/Real.cuh"
#include <memory>

#include "cpp/distribution/ParticleDistribution.h"
#include "cpp/constant/PhysicalConstants.h"	

class ParticleDistributionDisk : public ParticleDistribution {
public:
	ParticleDistributionDisk(
		std::shared_ptr<DistributionDensity> densityDistribution,
		Real centralMass,
		Vector3D<Real> meanPosition,
		Real thetaPosition,
		Real phiPosition,
    	bool clockwise,
		std::shared_ptr<Distribution> innerRadius,
		std::shared_ptr<Distribution> outerRadius, 
		std::shared_ptr<Distribution> eccentricity,
		// std::shared_ptr<Distribution3D> angularVelocityDistribution,
		// Where between the inner and outer radius the particles gather, on
		// a 0..1 scale. 0.5 spreads them evenly across the disk.
		Real positionBias = 0.5,
		Real G = PhysicalConstants::GRAVITATIONAL_CONSTANT
	);
	~ParticleDistributionDisk();

	Particle* getParticle() override;

private:
	std::shared_ptr<DistributionDensity> densityDistribution;
	Real centralMass;
	Vector3D<Real> meanPosition;
	Real thetaPosition;
	Real phiPosition;
    bool clockwise;
	std::shared_ptr<Distribution> innerRadius;
	std::shared_ptr<Distribution> outerRadius; 
	std::shared_ptr<Distribution> eccentricity;
	// std::shared_ptr<Distribution3D> angularVelocityDistribution;
	Real positionBias;
	Real G;
};