#pragma once
#include <memory>

#include "distribution/ParticleDistribution.h"
#include "constant/PhysicalConstants.h"	

class ParticleDistributionDisk : public ParticleDistribution {
public:
	ParticleDistributionDisk(
		std::shared_ptr<DistributionDensity> densityDistribution,
		float centralMass,
		Vector3D<float> meanPosition,
		float thetaPosition,
		float phiPosition,
    	bool clockwise,
		std::shared_ptr<Distribution> innerRadius,
		std::shared_ptr<Distribution> outerRadius, 
		std::shared_ptr<Distribution> eccentricity,
		// std::shared_ptr<Distribution3D> angularVelocityDistribution,
		float G = PhysicalConstants::GRAVITATIONAL_CONSTANT
	);
	~ParticleDistributionDisk();

	virtual Particle* getParticle();

private:
	std::shared_ptr<DistributionDensity> densityDistribution;
	float centralMass;
	Vector3D<float> meanPosition;
	float thetaPosition;
	float phiPosition;
    bool clockwise;
	std::shared_ptr<Distribution> innerRadius;
	std::shared_ptr<Distribution> outerRadius; 
	std::shared_ptr<Distribution> eccentricity;
	// std::shared_ptr<Distribution3D> angularVelocityDistribution;
	float G;
};