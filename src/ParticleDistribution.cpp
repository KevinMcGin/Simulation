#include "ParticleDistribution.h"



ParticleDistribution::ParticleDistribution(Distribution* massDistribution, Distribution* radiusDistribution, Distribution3D* positionDistrubtion, Distribution3D* velocityDistrubtion, Distribution3D* angularVelocityDistrubtion) :
	massDistribution(massDistribution),
	radiusDistribution(radiusDistribution),
	positionDistrubtion(positionDistrubtion),
	velocityDistrubtion(velocityDistrubtion),
	angularVelocityDistrubtion(angularVelocityDistrubtion)
{

}
