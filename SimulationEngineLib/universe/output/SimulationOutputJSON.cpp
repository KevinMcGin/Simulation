#include <string>

#include "universe/output/SimulationOutputJSON.h"

SimulationOutputJSON::SimulationOutputJSON(const char* outputFile) : SimulationOutput() {
	myfile.open(outputFile);
}

SimulationOutputJSON::~SimulationOutputJSON()
{
	myfile << buffer << "}" << std::endl;
	myfile.close();
}

void SimulationOutputJSON::output(std::vector<Particle*> particles, unsigned long time)
{
	if (time > 0) {
		buffer = buffer.append(",\n");
	}
	buffer = buffer.append("\"")
			.append(std::to_string(time))
			.append("\": [\n");
	unsigned int particleCount = particles.size();
	unsigned int i = 0;
	for (const auto& p : particles) {
		buffer = buffer.append("{ ")
			.append("\"r\": ")
			.append(std::to_string(p->radius))
			.append(",\n")
			.append("\"pos\": [")
			.append(std::to_string(p->position.x))
			.append(",")
			.append(std::to_string(p->position.y))
			.append(",")
			.append(std::to_string(p->position.z))
			.append("]}\n");
		if (++i < particleCount) {
			buffer = buffer.append(",\n");
		}
	}
	buffer = buffer.append("]");

	auto bufferLength = buffer.length();
	if (bufferLength >= maxBufferLength) {
		myfile << buffer;
		buffer = "";
	}
}
