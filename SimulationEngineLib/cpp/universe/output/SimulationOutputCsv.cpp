#include <string>
#include <sstream>

#include "cpp/universe/output/SimulationOutputCsv.h"

SimulationOutputCsv::SimulationOutputCsv(const char* outputFile) : SimulationOutputFile(outputFile) {
    appendToBuffer("frame,radius,postitionX,positionY,positionZ\n");    
}

SimulationOutputCsv::~SimulationOutputCsv() = default;

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 12)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

void SimulationOutputCsv::output(std::vector<Particle*> particles, unsigned long time) {
	for (const auto& p : particles) {
		appendToBuffer(std::to_string(time));
        appendToBuffer(",");
        appendToBuffer(to_string_with_precision(p->radius));
        appendToBuffer(",");
        appendToBuffer(to_string_with_precision(p->position.x));
        appendToBuffer(",");
        appendToBuffer(to_string_with_precision(p->position.y));
        appendToBuffer(",");
        appendToBuffer(to_string_with_precision(p->position.z));
        appendToBuffer("\n");
	}

	writeToBufferMaybe();
}
