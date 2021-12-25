#pragma once
#include <memory>

#include "ParticleDistribution.h"
#include "PhysicalConstants.h"	

class ParticleDistributionDisk : public ParticleDistribution
{
public:
	ParticleDistributionDisk(
		std::shared_ptr<DistributionDensity> densityDistribution,
		double centralMass,
		Vector3D meanPosition,
		double thetaPosition,
		double phiPosition,
    	bool clockwise,
		double innerRadius,
		double outerRadius, 
		double eccentricity,
		shared_ptr<Distribution3D> angularVelocityDistribution,
		double G = PhysicalConstants::GRAVITATIONAL_CONSTANT
	);
	~ParticleDistributionDisk();

	virtual Particle* getParticle();

private:
	std::shared_ptr<DistributionDensity> densityDistribution;
	double centralMass;
	Vector3D meanPosition;
	double thetaPosition;
	double phiPosition;
    bool clockwise;
	double innerRadius;
	double outerRadius; 
	double eccentricity;
	std::shared_ptr<Distribution3D> angularVelocityDistribution;
	double G;
};