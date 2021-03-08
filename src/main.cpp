#include "Particle.h"
#include "ParticleSimple.h"
#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.h"
#include "DistributionValue.h"
#include "../src/DistributionMassDensity.h"

#include <stdio.h>

int main()
{
	double meanMass = 0.01;
	Distribution* massDistrubtion = new DistributionSimple(meanMass, meanMass*0.9);
	Distribution* density = new DistributionValue(10000);
	DistributionDensity* densityDistribution = new DistributionMassDensity(massDistrubtion, density);
	Distribution3D* positionDistrubtion = new DistributionCircle({ 0,0,0 }, 2);
	Distribution3D* velocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0.005);
	Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
	ParticleDistributionSimple particleDistribution(densityDistribution, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
	SimulationInput* input = new SimulationInputRandomSimple(300, particleDistribution);

	SimulationOutput* output = new SimulationOutputJSON();

	Universe* universe = new UniverseImplSimple(input, output, 300);

	universe->run();

	delete universe;
	return 0;
}