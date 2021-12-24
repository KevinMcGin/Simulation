#include "SimulationInputRandomSimple.h"
#include "SimulationOutputJSON.h"
#include "UniverseImplSimple.h"
#include "DistributionValue.h"
#include "DistributionCircle.h"
#include "DistributionMassDensity.h"
#include "ParticleDistributionSimple.h"
#include "ParticleDistributionDisk.h"
#include "Timing.h"

#include <cargs.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	unsigned long particleCount = 50;
	unsigned int frameRate = 60;
	unsigned int seconds = 10;
	double meanMass = 0.01;	
	double starMass = 50;
	double meanSpeed = 0.04;
	double deltaSpeedFraction = 0.2;
	double outerRadius = 15;
	double meanDensity = 1000;
	const char* outputFile = "simulation_output/simulation_output.json";

	static struct cag_option options[] = {	   
		{'p',
		 "p",
		 "particle-count",
		 "Particle count value"},
		{'f',
		 "f",
		 "frame-rate",
		 "Frame rate of render"},
		{'s',
		 "s",
		 "seconds",
		 "Seconds of render"},	
		{'m',
		 "m",
		 "mean-mass",
		 "Mean mass of particles"},	
		 {'u',
		  "u",
		  "mean-density",
		  "Mean density of particles"},	
		{'c',
		 "c",
		  "star-mass",
		 "Mass of the central body"},
		{'v',
		 "v",
		 "mean-speed",
		 "Mean speed of particles"},
		{'d',
		 "d",
		 "delta-speed",
		 "Fractional variance +- of speed"},
		{'r',
		 "r",
		 "radius",
		 "Outer radius of the disk"},
		 {'o',
		  "o",
		  "output-file",
		  "Output file at simulation_output folder"},	  		 	   
		{'h',
		 "h",
		 "help",
   		 "VALUE",
		 "Shows the command help"}
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
			case 'u':{
				const char* value = cag_option_get_value(&context);
				meanDensity = atof(value);
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
			case 'o':{
				outputFile = cag_option_get_value(&context);
				break;}
			case 'h':{
				printf("Usage: ./SimulationEngine.exe [OPTION]...\n");
				cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
				return EXIT_SUCCESS;}
		}
	}

	double deltaSpeed = meanSpeed * deltaSpeedFraction;
	unsigned int endTime = seconds * frameRate;

	Vector3D meanPosition = {0,0,0};
	Distribution* massDistribution = new DistributionSimple(meanMass, meanMass*0.9);
	Distribution* density = new DistributionValue(meanDensity);
	DistributionDensity* densityDistribution = new DistributionMassDensity(massDistribution, density);
	DistributionDensity* distributionDensityStar = new DistributionMassDensity(new DistributionValue(starMass), density);
	Distribution3D* positionDistribution = new DistributionCircle(meanPosition, 0);
	Distribution3D* velocityDistribution = new DistributionCircle(meanPosition, 0);
	Distribution3D* angularVelocityDistribution = new DistributionCircle({ 0,0,0 }, 0);
	ParticleDistribution* particleDistributionDisk = new ParticleDistributionDisk(densityDistribution, starMass, meanPosition, 0, 0, false, 0, outerRadius, 1, angularVelocityDistribution);	
	ParticleDistribution* particleDistributionStar = new ParticleDistributionSimple(distributionDensityStar, positionDistribution, velocityDistribution, angularVelocityDistribution);
	SimulationInput* input = new SimulationInputRandomSimple(
		{ particleCount - 1, 1 },
		{ particleDistributionDisk, particleDistributionStar }
	);

	SimulationOutput* output = new SimulationOutputJSON(outputFile);

	Universe* universe = new UniverseImplSimple(input, output, endTime);
	universe->run();
	delete universe;
	return 0;
}