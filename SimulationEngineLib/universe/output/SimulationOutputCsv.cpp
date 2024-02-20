#include <string>

#include "universe/output/SimulationOutputCsv.h"

SimulationOutputCsv::SimulationOutputCsv(const char* outputFile) : SimulationOutputFile(outputFile) {
    appendToBuffer("frame,radius,postitionX,positionY,positionZ\n");    
}

SimulationOutputCsv::~SimulationOutputCsv() = default;

void SimulationOutputCsv::output(std::vector<Particle*> particles, unsigned long time) {
	for (const auto& p : particles) {
		appendToBuffer(std::to_string(time))
        appendToBuffer(",")
        appendToBuffer(std::to_string(p->radius))
        appendToBuffer(",")
        appendToBuffer(std::to_string(p->position.x))
        appendToBuffer(",")
        appendToBuffer(std::to_string(p->position.y))
        appendToBuffer(",")
        appendToBuffer(std::to_string(p->position.z))
        appendToBuffer("\n");
	}
	appendToBuffer("\n");

	writeToBufferMaybe();
}
