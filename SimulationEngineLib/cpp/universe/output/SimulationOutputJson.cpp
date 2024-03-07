#include <string>

#include "cpp/universe/output/SimulationOutputJson.h"

SimulationOutputJson::SimulationOutputJson(const char* outputFile) : SimulationOutputFile(outputFile) {
	appendToBuffer("{\n");
}

SimulationOutputJson::~SimulationOutputJson() {
	appendToBuffer("}");
	writeToBuffer();
}

void SimulationOutputJson::output(std::vector<Particle*> particles, unsigned long time) {
	if (time > 0) {
		appendToBuffer(",\n");
	}
	appendToBuffer("\"");
	appendToBuffer(std::to_string(time));
	appendToBuffer("\": [\n");
	unsigned int particleCount = particles.size();
	unsigned int i = 0;
	for (const auto& p : particles) {
		appendToBuffer("{ ");
		appendToBuffer("\"r\": ");
		appendToBuffer(std::to_string(p->radius));
		appendToBuffer(",\n");
		appendToBuffer("\"pos\": [");
		appendToBuffer(std::to_string(p->position.x));
		appendToBuffer(",");
		appendToBuffer(std::to_string(p->position.y));
		appendToBuffer(",");
		appendToBuffer(std::to_string(p->position.z));
		appendToBuffer("]}\n");
		if (++i < particleCount) {
			appendToBuffer(",\n");
		}
	}
	appendToBuffer("]");

	writeToBufferMaybe();
}
