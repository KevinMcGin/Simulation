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
#include <memory>

int printUsage(int exitStatus, cag_option options[]) {
	printf("Usage: ./SimulationEngine.exe [OPTION]...\n");
	cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
	return exitStatus;
}

int main(int argc, char *argv[]) {
	unsigned long particleCount = 50;
	unsigned int frameRate = 60;
	unsigned int seconds = 10;
	double meanMass = 0.01;	
	double starMass = 50;
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
			case 'p':
				particleCount = atol(cag_option_get_value(&context));
				break;
			case 'f':
				frameRate = atoi(cag_option_get_value(&context));
				break;
			case 's':
				seconds = atoi(cag_option_get_value(&context));
				break;
			case 'm':
				meanMass = atof(cag_option_get_value(&context));
				break;
			case 'u':
				meanDensity = atof(cag_option_get_value(&context));
				break;
			case 'c':
				starMass = atof(cag_option_get_value(&context));
				break;
			case 'r':
				outerRadius = atof(cag_option_get_value(&context));
				break;
			case 'o':
				outputFile = cag_option_get_value(&context);
				break;
			case 'h':
				return printUsage(EXIT_SUCCESS, options);
			default:
				return printUsage(EXIT_FAILURE, options);
		}
	}
	unsigned int endTime = seconds * frameRate;

	Vector3D meanPosition = {0,0,0};
	auto massDistribution = make_shared<DistributionSimple>(meanMass, meanMass*0.9);
	auto density = make_shared<DistributionValue>(meanDensity);
	auto densityDistribution = make_shared<DistributionMassDensity>(massDistribution, density);
	auto distributionDensityStar = make_shared<DistributionMassDensity>(make_shared<DistributionValue>(starMass), density);
	auto positionDistribution = make_shared<DistributionCircle>(meanPosition, 0);
	auto velocityDistribution = make_shared<DistributionCircle>(meanPosition, 0);
	auto angularVelocityDistribution = make_shared<DistributionCircle>(Vector3D(0, 0, 0), 0);
	auto particleDistributionDisk = make_shared<ParticleDistributionDisk>(densityDistribution, starMass, meanPosition, 0, 0, false, 0, outerRadius, 1, angularVelocityDistribution);	
	auto particleDistributionStar = make_shared<ParticleDistributionSimple>(distributionDensityStar, positionDistribution, velocityDistribution, angularVelocityDistribution);
	
	auto input = make_shared<SimulationInputRandomSimple>(
		vector<unsigned long> { particleCount - 1, 1 }, 
		vector<shared_ptr<ParticleDistribution>> { particleDistributionDisk, particleDistributionStar }		
	);
	auto output = make_shared<SimulationOutputJSON>(outputFile);

	auto universe = make_unique<UniverseImplSimple>(input, output, endTime);
	universe->run();
	return 0;
}