#include "Particle.h"
#include "ParticleSimple.h"
#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.h"
#include "DistributionValue.h"
#include "DistributionCircle.h"
#include "DistributionMassDensity.h"

#include <stdio.h>

int main()
{
	double particleCount = 300;
	unsigned int particleQuadrantCount = particleCount / 4.0;
	double meanMass = 0.01;
	Distribution* massDistrubtion = new DistributionSimple(meanMass, meanMass*0.9);
	Distribution* density = new DistributionValue(3000);
	DistributionDensity* densityDistribution = new DistributionMassDensity(massDistrubtion, density);
	DistributionDensity* distributionDensityStar = new DistributionMassDensity(new DistributionValue(50), density);
	double meanSpeed = 0.03;
	double deltaSpeed = meanSpeed * 0.2;
	double meanDistance = 2.5;
	double deltaDistance = 2.4;
	Distribution3D* positionDistrubtion1 = new DistributionCircle({ -meanDistance,0,0 }, deltaDistance);
	Distribution3D* positionDistrubtion2 = new DistributionCircle({ meanDistance,0,0 }, deltaDistance);
	Distribution3D* positionDistrubtion3 = new DistributionCircle({ 0,meanDistance,0 }, deltaDistance);
	Distribution3D* positionDistrubtion4 = new DistributionCircle({ 0,-meanDistance,0 }, deltaDistance);
	Distribution3D* positionDistrubtion5 = new DistributionCircle({ 0,0,0 }, 0);
	Distribution3D* velocityDistrubtion1 = new DistributionCircle({ 0,-meanSpeed,0 }, deltaSpeed);
	Distribution3D* velocityDistrubtion2 = new DistributionCircle({ 0,meanSpeed,0 }, deltaSpeed);
	Distribution3D* velocityDistrubtion3 = new DistributionCircle({ -meanSpeed,0,0 }, deltaSpeed);
	Distribution3D* velocityDistrubtion4 = new DistributionCircle({ meanSpeed,0,0 }, deltaSpeed);
	Distribution3D* velocityDistrubtion5 = new DistributionCircle({ 0,0,0 }, 0);
	Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
	ParticleDistributionSimple particleDistribution1(densityDistribution, positionDistrubtion1, velocityDistrubtion1, angularVelocityDistrubtion);
	ParticleDistributionSimple particleDistribution2(densityDistribution, positionDistrubtion2, velocityDistrubtion2, angularVelocityDistrubtion);
	ParticleDistributionSimple particleDistribution3(densityDistribution, positionDistrubtion3, velocityDistrubtion3, angularVelocityDistrubtion);
	ParticleDistributionSimple particleDistribution4(densityDistribution, positionDistrubtion4, velocityDistrubtion4, angularVelocityDistrubtion);
	ParticleDistributionSimple particleDistribution5(distributionDensityStar, positionDistrubtion5, velocityDistrubtion5, angularVelocityDistrubtion);
	SimulationInput* input = new SimulationInputRandomSimple({ particleQuadrantCount, particleQuadrantCount, particleQuadrantCount, particleQuadrantCount, 1 },
		{ particleDistribution1, particleDistribution2, particleDistribution3, particleDistribution4, particleDistribution5 });

	/*SimulationInput* input = new SimulationInputRandomSimple({ 1, 1 },
		{ 
			ParticleDistributionSimple(new DistributionMassDensity(new DistributionValue(400),new DistributionValue(10000)), new DistributionCircle({ 0,0,0 }, 0), new DistributionCircle({ 0,0,0 }, 0), new DistributionCircle({ 0,0,0 }, 0)),
			ParticleDistributionSimple(new DistributionMassDensity(new DistributionValue(0.01),new DistributionValue(10)), new DistributionCircle({ 1.5,0,0 }, 0), new DistributionCircle({ 0,0.1,0 }, 0), new DistributionCircle({ 0,0,0 }, 0))
		}
	);*/

	SimulationOutput* output = new SimulationOutputJSON();

	Universe* universe = new UniverseImplSimple(input, output, 3000);
	universe->run();
	delete universe;
	return 0;
}