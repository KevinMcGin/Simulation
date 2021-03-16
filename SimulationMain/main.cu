#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.h"
#include "DistributionValue.h"
#include "DistributionCircle.h"
#include "DistributionMassDensity.h"
#include "ParticleDistributionSimple.h"
#include "ParticleDistributionDisk.h"
#include "Timing.h"

#include <stdio.h>

int main()
{
	Timing::setTime();

	#ifdef USE_CUDA
    	std::cout << "CUDA: On" << std::endl;
	#else
    	std::cout << "CUDA: Off" << std::endl;
	#endif

	unsigned long particleCount = 100;
	unsigned long endTime = 1 * 60 * 60;
	double meanMass = 0.01;	
	double starMass = 50;
	double meanSpeed = 0.04;
	double deltaSpeed = meanSpeed * 0.2;
	double outerRadius = 15;
	Vector3D meanPosition = {0,0,0};
	Distribution* massDistrubtion = new DistributionSimple(meanMass, meanMass*0.9);
	Distribution* density = new DistributionValue(3000);
	DistributionDensity* densityDistribution = new DistributionMassDensity(massDistrubtion, density);
	DistributionDensity* distributionDensityStar = new DistributionMassDensity(new DistributionValue(starMass), density);
	Distribution3D* positionDistrubtion5 = new DistributionCircle(meanPosition, 0);
	Distribution3D* velocityDistrubtion5 = new DistributionCircle(meanPosition, 0);
	Distribution3D* angularVelocityDistrubtion = new DistributionCircle({ 0,0,0 }, 0);
	ParticleDistribution* particleDistributionDisk = new ParticleDistributionDisk(densityDistribution, starMass*2, meanPosition, 0, 0, false, 0, outerRadius, 1, angularVelocityDistrubtion);	
	ParticleDistribution* particleDistributionStar = new ParticleDistributionSimple(distributionDensityStar, positionDistrubtion5, velocityDistrubtion5, angularVelocityDistrubtion);
	SimulationInput* input = new SimulationInputRandomSimple({ particleCount, 1 },
		{ particleDistributionDisk, particleDistributionStar });

	/*SimulationInput* input = new SimulationInputRandomSimple({ 1, 1 },
		{ 
			ParticleDistributionSimple(new DistributionMassDensity(new DistributionValue(400),new DistributionValue(10000)), new DistributionCircle({ 0,0,0 }, 0), new DistributionCircle({ 0,0,0 }, 0), new DistributionCircle({ 0,0,0 }, 0)),
			ParticleDistributionSimple(new DistributionMassDensity(new DistributionValue(0.01),new DistributionValue(10)), new DistributionCircle({ 1.5,0,0 }, 0), new DistributionCircle({ 0,0.1,0 }, 0), new DistributionCircle({ 0,0,0 }, 0))
		}
	);*/

	SimulationOutput* output = new SimulationOutputJSON();

	Universe* universe = new UniverseImplSimple(input, output, endTime);
	universe->run();
	delete universe;
	return 0;
}