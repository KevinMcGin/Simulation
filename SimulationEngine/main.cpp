#include "universe/input/SimulationInputRandomSimple.h"
#include "universe/output/SimulationOutputJSON.h"
#include "universe/UniverseImplSimple.h"
#include "distribution/DistributionValue.h"
#include "distribution/DistributionCircle.h"
#include "distribution/DistributionMassDensity.h"
#include "distribution/ParticleDistributionSimple.h"
#include "distribution/ParticleDistributionDisk.h"
#include "util/Timing.h"

#include <cargs.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory>

const struct cag_option options[] = {	   
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

int printUsage(int exitStatus) {
	printf("Usage: ./SimulationEngine.exe [OPTION]...\n");
	// cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
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
				return printUsage(EXIT_SUCCESS);
			default:
				return printUsage(EXIT_FAILURE);
		}
	}
	unsigned int endTime = seconds * frameRate;

	Vector3D meanPosition = { 0, 0, 0 };
	auto massDistribution = std::make_shared<DistributionSimple>(meanMass, meanMass*0.9);
	auto density = std::make_shared<DistributionValue>(meanDensity);
	auto densityDistribution = std::make_shared<DistributionMassDensity>(massDistribution, density);
	auto distributionDensityStar = std::make_shared<DistributionMassDensity>(make_shared<DistributionValue>(starMass), density);
	auto positionDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	auto velocityDistribution = std::make_shared<DistributionCircle>(meanPosition, 0);
	auto angularVelocityDistribution = std::make_shared<DistributionCircle>(Vector3D(0, 0, 0), 0);
	auto innerRadiusDistribution = std::make_shared<DistributionValue>(0);
	auto outerRadiusDistribution = std::make_shared<DistributionValue>(outerRadius);
	auto eccentricityDistribution = std::make_shared<DistributionValue>(1);
	auto particleDistributionDisk = std::make_shared<ParticleDistributionDisk>(densityDistribution, starMass, meanPosition, 0, 0, false, innerRadiusDistribution, outerRadiusDistribution, eccentricityDistribution, angularVelocityDistribution);	
	auto particleDistributionStar = std::make_shared<ParticleDistributionSimple>(distributionDensityStar, positionDistribution, velocityDistribution, angularVelocityDistribution);
	
	auto input = std::make_shared<SimulationInputRandomSimple>(
		vector<unsigned long> { particleCount - 1, 1 }, 
		vector<std::shared_ptr<ParticleDistribution>> { particleDistributionDisk, particleDistributionStar }		
	);
	auto output = std::make_shared<SimulationOutputJSON>(outputFile);

	auto universe = std::make_unique<UniverseImplSimple>(input, output, endTime);
	universe->run();
	return 0;
}