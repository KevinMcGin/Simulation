#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.cuh"
#include "DistributionValue.h"
#include "DistributionCircle.h"
#include "DistributionMassDensity.h"
#include "ParticleDistributionSimple.h"
#include "ParticleDistributionDisk.h"
#include "Timing.h"

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

//Windows only
// #include "XGetopt.h"
//Unix only
//#include <unistd.h>


int main(int argc, TCHAR *argv[])
{
	Timing::setTime();
	TCHAR* x = argv[1];

	#ifdef USE_CUDA
    	std::cout << "CUDA: On" << std::endl;
	#else
    	std::cout << "CUDA: Off" << std::endl;
	#endif

	unsigned long particleCount = 50;
	unsigned int frameRate = 60;
	double seconds = 10;
	double meanMass = 0.01;	
	double starMass = 50;
	double meanSpeed = 0.04;
	double deltaSpeedFraction = 0.2;
	double outerRadius = 15;


	//Specifying the expected options
    //The two options l and b expect numbers as argument
    // static struct option long_options[] = {
    //     {"particleCount",      no_argument,       	0,  'c' },
    //     {"frameRate", 	       no_argument,       	0,  'f' },
    //     {"seconds",            required_argument, 	0,  's' },
    //     {"meanMass",           required_argument, 	0,  'm' },
    //     {"starMass",           required_argument, 	0,  't' },
    //     {"deltaSpeedFraction", required_argument,   0,  'd' },
    //     {"outerRadius",        required_argument, 	0,  'r' },
    //     {0,             	   0,                 	0,  0   }
    // };

	// int c;
	// while ((c = getopt(argc, argv, _T("c:f:s:m:t:v:d:r:"))) != EOF)
	// {
	// 	switch (c)
	// 	{
	// 		case _T('c'):
	// 			particleCount = atoi(optarg);
	// 			break;				
	// 		case _T('f'):
	// 			frameRate = atoi(optarg);
	// 			break;
	// 		case _T('s'): 
	// 			seconds = atoi(optarg);
	// 			break;
	// 		case _T('m'):
	// 			meanMass = atoi(optarg);
	// 			break;				
	// 		case _T('t'):
	// 			starMass = atoi(optarg);
	// 			break;				
	// 		case _T('v'):
	// 			meanSpeed = atoi(optarg);
	// 			break;
	// 		case _T('d'):
	// 			deltaSpeedFraction = atoi(optarg);
	// 			break;
	// 		case _T('r'):
	// 			outerRadius = atoi(optarg);
	// 			break;				
	// 		case _T('?'):
	// 			break;
	// 		default:
	// 			break;
	// 	}
	// }

	double deltaSpeed = meanSpeed * deltaSpeedFraction;
	unsigned int endTime = seconds * frameRate;

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