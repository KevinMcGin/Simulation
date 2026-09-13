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

		// A hard ceiling independent of whatever the caller (normally the Go
		// backend, which enforces its own cap — but this engine is directly
		// reachable on its own port too) asked for, so a huge particleCount
		// can't single-handedly exhaust memory/CPU here.
		const unsigned long maxParticleCount = 30000;

		long particleCount = 10;
		long frameRate = 1000;
		long seconds = 864000;
		long deltaTime = 864000;
		float meanMass = 0.01f;
		float starMass = 50;
		float outerRadius = 15;
		float meanDensity = 1000;

		if (req.has_param("particleCount")) {
			particleCount = atol(req.get_param_value("particleCount").c_str());
		}
		if (req.has_param("seconds")) {
			seconds = atol(req.get_param_value("seconds").c_str());
		}
		if (req.has_param("frameRate")) {
			frameRate = atol(req.get_param_value("frameRate").c_str());
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

		// frameRate and deltaTime are divisors just below (and particleCount
		// drives allocation size / loop counts further down in the engine) —
		// a zero, negative, or unparsable ("abc" -> atol gives 0) value here
		// previously fell straight through into that division, which is a
		// crash (integer division by zero) rather than a normal error, and
		// would have taken the whole server — every in-flight and future
		// simulation, not just this request — down with it.
		if (particleCount <= 0) {
			res.status = 400;
			res.set_content("particleCount must be greater than 0", "text/plain");
			return;
		}
		if ((unsigned long)particleCount > maxParticleCount) {
			res.status = 400;
			res.set_content("particleCount must be less than " + std::to_string(maxParticleCount), "text/plain");
			return;
		}
		if (seconds <= 0) {
			res.status = 400;
			res.set_content("seconds must be greater than 0", "text/plain");
			return;
		}
		if (frameRate <= 0) {
			res.status = 400;
			res.set_content("frameRate must be greater than 0", "text/plain");
			return;
		}
		if (deltaTime <= 0) {
			res.status = 400;
			res.set_content("deltaTime must be greater than 0", "text/plain");
			return;
		}
		if (meanMass <= 0 || meanDensity <= 0 || starMass <= 0 || outerRadius <= 0) {
			res.status = 400;
			res.set_content("meanMass, meanDensity, starMass and outerRadius must all be greater than 0", "text/plain");
			return;
		}

		unsigned long deltaFrameRate = (unsigned long)deltaTime / (unsigned long)frameRate;
		float frameRateTime = (float)frameRate / (float)deltaTime;
		unsigned int endTime = (unsigned int)((unsigned long)seconds * frameRateTime);

		if (deltaFrameRate == 0) {
			res.status = 400;
			res.set_content("frameRate must not be greater than deltaTime", "text/plain");
			return;
		}

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

		// Everything above is just parsing/validating request parameters;
		// everything below actually drives the simulation engine and does
		// file I/O, either of which can throw (or, for the file, silently
		// produce nothing) for reasons that have nothing to do with the
		// request itself (disk full, engine hitting a bad internal state,
		// etc) — caught here so that failure comes back as a normal 500
		// response instead of an unhandled exception taking the process,
		// and every other in-flight simulation, down with it.
		try {
			auto simulationInputDistributionStarSystem = std::make_unique<SimulationInputDistributionStarSystem>(
				meanMass,
				meanDensity,
				starMass,
				outerRadius,
				(unsigned long)particleCount
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
			if (outputJson.empty()) {
				std::cerr << "Simulation produced no output for " << outputFile << "\n";
				res.status = 500;
				res.set_content("Simulation did not produce any output", "text/plain");
				return;
			}
			res.status = 200;
			res.set_content(outputJson, "text/csv");
		} catch (const std::exception &e) {
			std::cerr << "Simulation failed: " << e.what() << "\n";
			res.status = 500;
			res.set_content(std::string("Simulation failed: ") + e.what(), "text/plain");
		} catch (...) {
			std::cerr << "Simulation failed with an unknown error\n";
			res.status = 500;
			res.set_content("Simulation failed with an unknown error", "text/plain");
		}
	});

	std::cout << "Simulation server running\n";
	svr.listen("0.0.0.0", 8895);
}