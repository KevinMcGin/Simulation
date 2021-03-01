﻿#pragma once
#include "Distribution.h"
#include "Distribution3D.h"
#include "Particle.h"

class ParticleDistribution {
public:
	ParticleDistribution(Distribution* massDistribution, Distribution* radiusDistribution, Distribution3D* positionDistrubtion, Distribution3D* velocityDistrubtion, Distribution3D* angularVelocityDistrubtion):
		massDistribution(massDistribution),
		radiusDistribution(radiusDistribution),
		positionDistrubtion(positionDistrubtion),
		velocityDistrubtion(velocityDistrubtion),
		angularVelocityDistrubtion(angularVelocityDistrubtion) 
		{};

	virtual Particle* getParticle() = 0;

protected:
	Distribution* massDistribution;
	Distribution* radiusDistribution;
	Distribution3D* positionDistrubtion;
	Distribution3D* velocityDistrubtion;
	Distribution3D* angularVelocityDistrubtion;
};