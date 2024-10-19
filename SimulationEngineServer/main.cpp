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
#include <cpp/constant/PhysicalConstants.h>

int main(int argc, char *argv[]) {
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
		unsigned long particleCount = 10;
		unsigned int frameRate = 1000;
		unsigned long seconds = 864000;
		unsigned long deltaTime = 864000;
		float meanMass = 0.01f;	
		float starMass = 50;
		float outerRadius = 15;
		float meanDensity = 1000;

		if (req.has_param("particleCount")) {
			particleCount = atoi(req.get_param_value("particleCount").c_str());
		}
		if (req.has_param("seconds")) {
			seconds = atoi(req.get_param_value("seconds").c_str());
		}
		if (req.has_param("frameRate")) {
			frameRate = atoi(req.get_param_value("frameRate").c_str());
		}
		if (req.has_param("deltaTime")) {
			deltaTime = atol(req.get_param_value("deltaTime").c_str());
		}
		if (req.has_param("meanMass")) {
			meanMass = atof(req.get_param_value("meanMass").c_str());
		}
		if (req.has_param("meanDensity")) {
			meanDensity = atof(req.get_param_value("meanDensity").c_str());
		}
		if (req.has_param("starMass")) {
			starMass = atof(req.get_param_value("starMass").c_str());
		}
		if (req.has_param("outerRadius")) {
			outerRadius = atof(req.get_param_value("outerRadius").c_str());
		}

		unsigned long deltaFrameRate = deltaTime / frameRate;
		float frameRateTime = (float)frameRate / (float)deltaTime;
		unsigned int endTime = seconds * frameRateTime;
		
		std::cout << PhysicalConstants::GRAVITATIONAL_CONSTANT << " GRAVITATIONAL_CONSTANT\n";
		std::cout << PhysicalConstants::SPEED_OF_LIGHT << " SPEED_OF_LIGHT\n";
		std::cout << particleCount << " particle count\n";
		std::cout << seconds << " seconds\n";
		std::cout << frameRate << " frame rate\n";
		std::cout << deltaTime << " delta time\n";
		std::cout << deltaFrameRate << " delta frame rate\n";
		std::cout << frameRateTime << " frame rate time\n";
		std::cout << endTime << " end time\n";
		std::cout << meanMass << " mean mass\n";
		std::cout << meanDensity << " mean density\n";
		std::cout << starMass << " star mass\n";
		std::cout << outerRadius << " outer radius\n";

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