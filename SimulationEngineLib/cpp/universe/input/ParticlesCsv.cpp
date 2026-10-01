#include "cpp/universe/input/ParticlesCsv.h"
#include "cpp/universe/input/particleInput/ParticleInput.h"
#include "cpp/particle/ParticleSimple.h"

#include <memory>
#include <sstream>
#include <string>

namespace {
	std::vector<std::string> split(const std::string& s, char delimiter) {
		std::vector<std::string> splits;
		std::string split;
		std::istringstream ss(s);
		while (std::getline(ss, split, delimiter)) {
			splits.push_back(split);
		}
		return splits;
	}

	// Reads one line, dropping the carriage return a CSV written on Windows
	// leaves on the end of it. Used for the header as well as the rows:
	// left in place there, the last column's name is "velocityZ\r", which
	// matches no known field and fails the whole document.
	bool readLine(std::istream& csv, std::string& line) {
		if (!std::getline(csv, line, '\n')) {
			return false;
		}
		if (!line.empty() && line.back() == '\r') {
			line.pop_back();
		}
		return true;
	}

	void deleteParticles(std::vector<Particle*>& particles) {
		for (auto particle : particles) {
			delete particle;
		}
		particles.clear();
	}
}

std::vector<Particle*> ParticlesCsv::parse(std::istream& csv) {
	std::string line;
	readLine(csv, line);
	// Throws if a column is not one the engine knows, which is the right
	// moment to give up: a misnamed column means the rows beneath it are
	// not the quantities they appear to be.
	ParticleInput particleInput(split(line, ','));

	std::vector<Particle*> particles;
	// Looping on getline rather than on eof(): eof() only becomes true
	// after a read has already failed, so a document ending in a newline —
	// as anything written by ParticleStateCsv does — got one more pass with
	// an empty line, and quietly gained a massless particle sitting at the
	// origin that nobody asked for.
	while (readLine(csv, line)) {
		if (line.empty()) {
			continue;
		}

		//Todo: Particle type created depends on headers available
		auto particle = new ParticleSimple(
			0, 0, { 0, 0, 0, }, { 0, 0, 0, }
		);
		try {
			particleInput.set(particle, split(line, ','));
		} catch (...) {
			// An unreadable row abandons the whole document, so everything
			// read so far — and the particle this row had already begun —
			// has nobody left to free it.
			delete particle;
			deleteParticles(particles);
			throw;
		}
		particles.push_back(particle);
	}

	return particles;
}
