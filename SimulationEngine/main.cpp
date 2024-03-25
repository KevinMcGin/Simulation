#include "cpp/universe/input/SimulationInputCsv.h"
#include "cpp/universe/output/SimulationOutputJson.h"
#include "cpp/universe/UniverseImplSimple.h"
#include "util/Timing.h"
#include <cpp/distribution/SimulationInputDistributionStarSystem.h>

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
	{'d',
		"d",
		"delta-time",
		"Delta time per frame of render, in seconds"},	
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
	unsigned long seconds = 10;
	unsigned long deltaTime = 1;
	float meanMass = 0.01f;	
	float starMass = 50;
	float outerRadius = 15;
	float meanDensity = 1000;
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
				seconds = atol(cag_option_get_value(&context));
				break;
			case 'd':
				deltaTime = atol(cag_option_get_value(&context));
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
	unsigned long deltaFrameRate = deltaTime / frameRate;
	float frameRateTime = (float)frameRate / (float)deltaTime;
	std::cout << seconds << " seconds" << std::endl;
	std::cout << frameRate << " frame rate" << std::endl;
	std::cout << deltaTime << " delta time" << std::endl;
	unsigned int endTime = seconds * frameRateTime;

	auto simulationInputDistributionStarSystem = std::make_unique<SimulationInputDistributionStarSystem>(
		meanMass,
		meanDensity,
		starMass,
		outerRadius,
		particleCount
	);

	auto input = simulationInputDistributionStarSystem->getStarSystemDistribution();

	// auto input = std::make_shared<SimulationInputCsv>(
	// 	"config/input/particlesInput.csv"
	// );
	auto output = std::make_shared<SimulationOutputJson>(outputFile);

	auto universe = std::make_unique<UniverseImplSimple>(
		input,
		output, 
		endTime,
		deltaFrameRate
	);
	universe->run();
	return 0;
}