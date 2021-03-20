#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.cuh"
#include "DistributionValue.h"
#include "DistributionCircle.h"
#include "DistributionMassDensity.h"
#include "ParticleDistributionSimple.h"
#include "ParticleDistributionDisk.h"
#include "Timing.h"

#include <cargs.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	Timing::setTime();

	unsigned long particleCount = 50;
	unsigned int frameRate = 60;
	double seconds = 10;
	double meanMass = 0.01;	
	double starMass = 50;
	double meanSpeed = 0.04;
	double deltaSpeedFraction = 0.2;
	double outerRadius = 15;

	static struct cag_option options[] = {	   
		{/*.identifier =*/ 'p',
		  /*.access_letters =*/ "p",
		  /*.access_name =*/ "particle-count",
		  /*.description =*/ "Particle count value"},
		{/*.identifier =*/ 'f',
		  /*.access_letters =*/ "f",
		  /*.access_name =*/ "frame-rate",
		  /*.description =*/ "Frame rate of render"},
		{/*.identifier =*/ 's',
		  /*.access_letters =*/ "s",
		  /*.access_name =*/ "seconds",
		  /*.description =*/ "Seconds of render"},	
		{/*.identifier =*/ 'm',
		  /*.access_letters =*/ "m",
		  /*.access_name =*/ "mean-mass",
		  /*.description =*/ "Mean mass of particles"},	
		{/*.identifier =*/ 'c',
		  /*.access_letters =*/ "c",
		  /*.access_name =*/ "star-mass",
		  /*.description =*/ "Mass of the central body"},
		{/*.identifier =*/ 'v',
		  /*.access_letters =*/ "v",
		  /*.access_name =*/ "mean-speed",
		  /*.description =*/ "Mean speed of particles"},
		{/*.identifier =*/ 'd',
		  /*.access_letters =*/ "d",
		  /*.access_name =*/ "delta-speed",
		  /*.description =*/ "Fractional variance +- of speed"},
		{/*.identifier =*/ 'r',
		  /*.access_letters =*/ "r",
		  /*.access_name =*/ "radius",
		  /*.description =*/ "Outer radius of the disk"},	  		 	   
		{/*.identifier =*/ 'h',
		  /*.access_letters =*/ "h",
		  /*.access_name =*/ "help",
   		  /*.value_name =*/ "VALUE",
		  /*.description =*/ "Shows the command help"}
	};

	char identifier;
	cag_option_context context;
	cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
	while (cag_option_fetch(&context)) {
		identifier = cag_option_get(&context);
		switch (identifier) {
			case 'p':{
				const char* value = cag_option_get_value(&context);
				particleCount = atol(value);
				break;}
			case 'f':{
				const char* value = cag_option_get_value(&context);
				frameRate = atoi(value);
				break;}
			case 's':{
				const char* value = cag_option_get_value(&context);
				seconds = atof(value);
				break;}
			case 'm':{
				const char* value = cag_option_get_value(&context);
				meanMass = atof(value);
				break;}
			case 'c':{
				const char* value = cag_option_get_value(&context);
				starMass = atof(value);
				break;}
			case 'v':{
				const char* value = cag_option_get_value(&context);
				meanSpeed = atof(value);
				break;}
			case 'd':{
				const char* value = cag_option_get_value(&context);
				deltaSpeedFraction = atof(value);
				break;}
			case 'r':{
				const char* value = cag_option_get_value(&context);
				outerRadius = atof(value);
				break;}
			case 'h':{
				printf("Usage: ./SimulationMain.exe [OPTION]...\n");
				cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
				return EXIT_SUCCESS;}
		}
	}

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

	SimulationOutput* output = new SimulationOutputJSON();

	Universe* universe = new UniverseImplSimple(input, output, endTime);
	universe->run();
	delete universe;
	return 0;
}