#include "cpp/universe/input/SimulationInputCsv.h"
#include "cpp/universe/output/SimulationOutputCsv.h"
#include "cpp/universe/UniverseImplSimple.h"
#include "util/Timing.h"
#include <cpp/distribution/SimulationInputDistributionStarSystem.h>

#include <stdbool.h>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <memory>
#include <filesystem>

// #define CPPHTTPLIB_OPENSSL_SUPPOR
#include "cpp/util/FileUtil.h"
#include "httplib.h"
#include <cpp/constant/PhysicalConstants.h>
#include <cpp/law/LawConfig.h>

// Start this through scripts/server.sh rather than running the binary
// directly: the script exports SIMULATION_USE_GPU from
// config/project.config, and left unset Universe::Universe reads it as
// true. On a CPU-only build that runs the do-nothing mocks in gpuMock, so
// every request still answers 200 with frames in which nothing has moved.
// The "Running on CPU"/"Running on GPU" line below says which it picked.
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
		// Simulated seconds per second of playback, and a float: the step it
		// divides into (deltaTime / frameRate) is a fraction of a second for
		// any run watched at a reasonable frame rate.
		float deltaTime = 864000;
		// Starts as the full set of laws and the star system this endpoint
		// has always generated, so a caller that sends none of the
		// parameters below gets the same universe it ran before any of it
		// was configurable.
		StarSystemConfig starSystem;
		LawConfig lawConfig;

		// Unreadable input is reported rather than absorbed. atof/atol answer
		// a value they can't parse with 0, or with however much of it they
		// did understand — "1e+07" arriving with its plus decoded as a space
		// reads as 1, which is not an error anywhere and just runs a
		// different simulation than the one that was asked for.
		std::string parseError;
		auto noteParseError = [&parseError](const char* name, const char* expected) {
			if (parseError.empty()) {
				parseError = std::string(name) + " must be " + expected;
			}
		};
		auto longParam = [&](const char* name, long fallback) -> long {
			if (!req.has_param(name)) {
				return fallback;
			}
			const std::string raw = req.get_param_value(name);
			try {
				size_t consumed = 0;
				const long value = std::stol(raw, &consumed);
				if (consumed != raw.size()) {
					throw std::invalid_argument("trailing characters");
				}
				return value;
			} catch (const std::exception &) {
				noteParseError(name, "a whole number");
				return fallback;
			}
		};
		auto floatParam = [&](const char* name, float fallback) -> float {
			if (!req.has_param(name)) {
				return fallback;
			}
			const std::string raw = req.get_param_value(name);
			try {
				size_t consumed = 0;
				const float value = std::stof(raw, &consumed);
				if (consumed != raw.size()) {
					throw std::invalid_argument("trailing characters");
				}
				return value;
			} catch (const std::exception &) {
				noteParseError(name, "a number");
				return fallback;
			}
		};

		particleCount = longParam("particleCount", particleCount);
		seconds = longParam("seconds", seconds);
		frameRate = longParam("frameRate", frameRate);
		deltaTime = floatParam("deltaTime", deltaTime);

		starSystem.meanMass = floatParam("meanMass", starSystem.meanMass);
		starSystem.massSpread = floatParam("massSpread", starSystem.massSpread);
		starSystem.meanDensity = floatParam("meanDensity", starSystem.meanDensity);
		starSystem.densitySpread = floatParam("densitySpread", starSystem.densitySpread);
		starSystem.starMass = floatParam("starMass", starSystem.starMass);
		// Both fall back to what they were fixed to before they could be set
		// on their own: the star took the disk's density, and the disk
		// orbited the star's actual mass.
		starSystem.starDensity = floatParam("starDensity", starSystem.meanDensity);
		starSystem.diskCentralMass = floatParam("diskCentralMass", starSystem.starMass);
		starSystem.innerRadius = floatParam("innerRadius", starSystem.innerRadius);
		starSystem.outerRadius = floatParam("outerRadius", starSystem.outerRadius);
		starSystem.positionBias = floatParam("positionBias", starSystem.positionBias);

		if (!parseError.empty()) {
			res.status = 400;
			res.set_content(parseError, "text/plain");
			return;
		}

		if (req.has_param("laws")) {
			auto error = lawConfig.setLaws(req.get_param_value("laws"));
			if (!error.empty()) {
				res.status = 400;
				res.set_content(error, "text/plain");
				return;
			}
		}
		if (req.has_param("momentum")) {
			auto error = lawConfig.setMomentum(req.get_param_value("momentum"));
			if (!error.empty()) {
				res.status = 400;
				res.set_content(error, "text/plain");
				return;
			}
		}
		if (req.has_param("gravitationalConstant")) {
			auto error = lawConfig.setGravitationalConstant(req.get_param_value("gravitationalConstant"));
			if (!error.empty()) {
				res.status = 400;
				res.set_content(error, "text/plain");
				return;
			}
		}

		// frameRate and deltaTime are divisors just below (and particleCount
		// drives allocation size / loop counts further down in the engine) —
		// a zero, negative, or unparsable ("abc" -> atol gives 0) value here
		// previously fell straight through into that division, which was a
		// crash (integer division by zero) rather than a normal error, and
		// would have taken the whole server — every in-flight and future
		// simulation, not just this request — down with it. The step is a
		// float now, so a zero there divides to infinity instead, which is
		// no better: it casts to a meaningless frame count.
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
		if (starSystem.meanMass <= 0 || starSystem.meanDensity <= 0 || starSystem.starMass <= 0 ||
			starSystem.starDensity <= 0 || starSystem.diskCentralMass <= 0 || starSystem.outerRadius <= 0) {
			res.status = 400;
			res.set_content("meanMass, meanDensity, starMass, starDensity, diskCentralMass and outerRadius must all be greater than 0", "text/plain");
			return;
		}
		// A spread of 1 or more takes the low end of the range to zero or
		// past it, which is a particle with no mass or a negative density.
		if (starSystem.massSpread < 0 || starSystem.massSpread >= 1 ||
			starSystem.densitySpread < 0 || starSystem.densitySpread >= 1) {
			res.status = 400;
			res.set_content("massSpread and densitySpread must be at least 0 and less than 1", "text/plain");
			return;
		}
		// Either end is allowed: it collapses the disk onto one of its radii,
		// which is a coherent thing to ask for rather than a bias at all.
		if (starSystem.positionBias < 0 || starSystem.positionBias > 1) {
			res.status = 400;
			res.set_content("positionBias must be at least 0 and at most 1", "text/plain");
			return;
		}
		if (starSystem.innerRadius < 0 || starSystem.innerRadius >= starSystem.outerRadius) {
			res.status = 400;
			res.set_content("innerRadius must be at least 0 and less than outerRadius", "text/plain");
			return;
		}

		// How much simulated time one frame covers, which is what the engine
		// steps by, and how many frames that leaves for the run.
		float simSecondsPerFrame = deltaTime / (float)frameRate;
		unsigned int endTime = (unsigned int)((float)seconds * ((float)frameRate / deltaTime));

		if (endTime == 0) {
			res.status = 400;
			res.set_content("the run is too short to produce a single frame: raise seconds or frameRate, or lower deltaTime", "text/plain");
			return;
		}

		starSystem.particleCount = (unsigned long)particleCount;

		std::cout << PhysicalConstants::GRAVITATIONAL_CONSTANT << " GRAVITATIONAL_CONSTANT\n";
		std::cout << PhysicalConstants::SPEED_OF_LIGHT << " SPEED_OF_LIGHT\n";
		std::cout << particleCount << " particle count\n";
		std::cout << seconds << " seconds\n";
		std::cout << frameRate << " frame rate\n";
		std::cout << deltaTime << " delta time\n";
		std::cout << simSecondsPerFrame << " simulated seconds per frame\n";
		std::cout << endTime << " end time\n";
		std::cout << starSystem.meanMass << " mean mass\n";
		std::cout << starSystem.massSpread << " mass spread\n";
		std::cout << starSystem.meanDensity << " mean density\n";
		std::cout << starSystem.densitySpread << " density spread\n";
		std::cout << starSystem.starMass << " star mass\n";
		std::cout << starSystem.starDensity << " star density\n";
		std::cout << starSystem.diskCentralMass << " disk central mass\n";
		std::cout << starSystem.innerRadius << " inner radius\n";
		std::cout << starSystem.outerRadius << " outer radius\n";
		std::cout << starSystem.positionBias << " position bias\n";
		std::cout << lawConfig.isCollisionCoalesceEnabled << " collision coalesce enabled\n";
		std::cout << lawConfig.isNewtonGravityEnabled << " newton gravity enabled\n";
		std::cout << lawConfig.isNewtonFirstLawEnabled << " newton first law enabled\n";
		std::cout << (lawConfig.momentum == MOMENTUM_EINSTEIN) << " is einstein momentum\n";
		std::cout << lawConfig.gravitationalConstant << " gravitational constant\n";

		// Everything above is just parsing/validating request parameters;
		// everything below actually drives the simulation engine and does
		// file I/O, either of which can throw (or, for the file, silently
		// produce nothing) for reasons that have nothing to do with the
		// request itself (disk full, engine hitting a bad internal state,
		// etc) — caught here so that failure comes back as a normal 500
		// response instead of an unhandled exception taking the process,
		// and every other in-flight simulation, down with it.
		try {
			auto simulationInputDistributionStarSystem = std::make_unique<SimulationInputDistributionStarSystem>(starSystem);

			auto input = simulationInputDistributionStarSystem->getStarSystemDistribution();

			// auto input = std::make_shared<SimulationInputCsv>(
			// 	"config/input/particlesInput.csv"
			// );
			auto output = std::make_shared<SimulationOutputCsv>(outputFile);

			auto universe = std::make_unique<UniverseImplSimple>(
				std::move(input),
				output,
				endTime,
				simSecondsPerFrame,
				UNDEFINED,
				lawConfig
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