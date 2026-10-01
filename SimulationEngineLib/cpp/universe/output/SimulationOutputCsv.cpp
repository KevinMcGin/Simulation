#include <string>

#include "cpp/universe/output/SimulationOutputCsv.h"
#include "cpp/util/CsvNumber.h"

SimulationOutputCsv::SimulationOutputCsv(const char* outputFile) : SimulationOutputFile(outputFile) {
    appendToBuffer("frame,radius,positionX,positionY,positionZ\n");    
}

SimulationOutputCsv::~SimulationOutputCsv() = default;

void SimulationOutputCsv::output(std::vector<Particle*> particles, unsigned long time) {
	for (const auto& p : particles) {
		appendToBuffer(std::to_string(time));
        appendToBuffer(",");
        appendToBuffer(CsvNumber::format(p->radius));
        appendToBuffer(",");
        appendToBuffer(CsvNumber::format(p->position.x));
        appendToBuffer(",");
        appendToBuffer(CsvNumber::format(p->position.y));
        appendToBuffer(",");
        appendToBuffer(CsvNumber::format(p->position.z));
        appendToBuffer("\n");
	}

	writeToBufferMaybe();
}
