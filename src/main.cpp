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
	Distribution* massDistrubtion = new DistributionSimple(0.000001, 0.00009);
	Distribution* density = new DistributionValue(100);
	DistributionDensity* densityDistribution = new DistributionMassDensity(massDistrubtion, density);
	Distribution3D* positionDistrubtion = new DistributionCircle({ 0,0,0 }, 2);
	Distribution3D* velocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0.5);
	Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
	ParticleDistributionSimple particleDistribution(densityDistribution, positionDistrubtion, velocityDistrubtion, angularVelocityDistrubtion);
	SimulationInput* input = new SimulationInputRandomSimple(30, particleDistribution);

	SimulationOutput* output = new SimulationOutputJSON();

	Universe* universe = new UniverseImplSimple(input, output, 30000);

	universe->run();

	delete universe;
	return 0;
}