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
	unsigned int frameRate = 60;
	unsigned long seconds = 10;
	// Simulated seconds per second of playback; the step it divides into
	// (deltaTime / frameRate) is a fraction of a second at any real frame
	// rate, so it is a float rather than a whole number of seconds.
	float deltaTime = 1;
	// Everything about the star system the run starts from, on its defaults
	// except for what the options below set.
	StarSystemConfig starSystem;
	starSystem.particleCount = 50;
	const char* outputFile = "simulation_output/simulation_output.json";

	char identifier;
	cag_option_context context;
	cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
	while (cag_option_fetch(&context)) {
		identifier = cag_option_get(&context);
		switch (identifier) {
			case 'p':
				starSystem.particleCount = atol(cag_option_get_value(&context));
				break;
			case 'f':
				frameRate = atoi(cag_option_get_value(&context));
				break;
			case 's':
				seconds = atol(cag_option_get_value(&context));
				break;
			case 'd':
				deltaTime = atof(cag_option_get_value(&context));
				break;			
			case 'm':
				starSystem.meanMass = atof(cag_option_get_value(&context));
				break;
			case 'u':
				starSystem.meanDensity = atof(cag_option_get_value(&context));
				break;
			case 'c':
				starSystem.starMass = atof(cag_option_get_value(&context));
				break;
			case 'r':
				starSystem.outerRadius = atof(cag_option_get_value(&context));
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
	float simSecondsPerFrame = deltaTime / (float)frameRate;
	std::cout << seconds << " seconds\n";
	std::cout << frameRate << " frame rate\n";
	std::cout << deltaTime << " delta time\n";
	std::cout << simSecondsPerFrame << " simulated seconds per frame\n";
	unsigned int endTime = (unsigned int)((float)seconds * ((float)frameRate / deltaTime));

	// The star mass the disk orbits is the star's own unless a run says
	// otherwise, which this command line has no option for yet.
	starSystem.diskCentralMass = starSystem.starMass;
	starSystem.starDensity = starSystem.meanDensity;

	auto simulationInputDistributionStarSystem = std::make_unique<SimulationInputDistributionStarSystem>(starSystem);

	auto input = simulationInputDistributionStarSystem->getStarSystemDistribution();

	// auto input = std::make_shared<SimulationInputCsv>(
	// 	"config/input/particlesInput.csv"
	// );
	auto output = std::make_unique<SimulationOutputJson>(outputFile);

	auto universe = std::make_unique<UniverseImplSimple>(
		std::move(input),
		std::move(output), 
		endTime,
		simSecondsPerFrame
	);
	universe->run();
	return 0;
}