#include "cpp/universe/input/SimulationInputCsv.h"
#include "cpp/universe/output/SimulationOutputCsv.h"
#include "cpp/universe/UniverseImplSimple.h"
#include "util/Timing.h"
#include <cpp/distribution/SimulationInputDistributionStarSystem.h>

#include <stdbool.h>
#include <stdlib.h>
#include <memory>
#include <filesystem>

// #define CPPHTTPLIB_OPENSSL_SUPPOR
#include "cpp/util/FileUtil.h"
#include "httplib.h"

int main(int argc, char *argv[]) {
	unsigned long particleCount = 50;
	unsigned int frameRate = 60;
	unsigned long seconds = 10;
	unsigned long deltaTime = 1;
	float meanMass = 0.01f;	
	float starMass = 50;
	float outerRadius = 15;
	float meanDensity = 1000;
	const char* outputFile = "simulation_output/simulation_output.csv";


	if (!std::filesystem::is_directory("simulation_output") || !std::filesystem::exists("simulation_output")) { 
		std::filesystem::create_directory("simulation_output"); 
	}

	// HTTP
	httplib::Server svr;

	// HTTPS
	// httplib::SSLServer svr;

	svr.Get("/api", [](const httplib::Request &req, httplib::Response &res) {
		std::cout << "Sim GET /api\n";
		res.set_content("General Kenobi!", "text/plain");
	});

	svr.Post("/api/simulation", [&](const httplib::Request &req, httplib::Response &res) {
		std::cout << "Sim POST /api/simulation\n";
		unsigned long deltaFrameRate = deltaTime / frameRate;
		float frameRateTime = (float)frameRate / (float)deltaTime;
		std::cout << seconds << " seconds\n";
		std::cout << frameRate << " frame rate\n";
		std::cout << deltaTime << " delta time\n";
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
		auto output = std::make_shared<SimulationOutputCsv>(outputFile);

		auto universe = std::make_unique<UniverseImplSimple>(
			std::move(input),
			output, 
			endTime,
			deltaFrameRate
		);
		universe->run();
		output->close();
		auto outputJson = FileUtil::fileToString(outputFile);
		res.set_content(outputJson, "text/csv");
	});

	std::cout << "Simulation server running\n";
	svr.listen("0.0.0.0", 8895);
}