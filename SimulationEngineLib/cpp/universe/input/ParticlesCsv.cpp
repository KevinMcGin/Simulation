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

	// Whether a line names columns rather than carrying a particle. Every
	// value in this format is a number, so a first cell that is not one is
	// a header — which is how several CSV documents concatenated together
	// are read as one. That matters because the inputs are additive and
	// each source brings its own header: a generated solar system and a
	// file someone pasted need not even name their columns in the same
	// order, so they cannot simply be merged under one.
	bool isHeader(const std::string& firstCell) {
		try {
			std::size_t consumed = 0;
			std::stod(firstCell, &consumed);
			return consumed != firstCell.size();
		} catch (const std::exception&) {
			return true;
		}
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
	auto particleInput = std::make_unique<ParticleInput>(split(line, ','));

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

		std::vector<std::string> values = split(line, ',');
		if (!values.empty() && isHeader(values.front())) {
			// A second document begins here; its columns describe the rows
			// that follow, not the ones above.
			try {
				particleInput = std::make_unique<ParticleInput>(values);
			} catch (...) {
				deleteParticles(particles);
				throw;
			}
			continue;
		}

		//Todo: Particle type created depends on headers available
		auto particle = new ParticleSimple(
			0, 0, { 0, 0, 0, }, { 0, 0, 0, }
		);
		try {
			particleInput->set(particle, values);
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
