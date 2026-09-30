#include <string>
#include <sstream>

#include "cpp/universe/output/SimulationOutputCsv.h"

SimulationOutputCsv::SimulationOutputCsv(const char* outputFile) : SimulationOutputFile(outputFile) {
    appendToBuffer("frame,radius,postitionX,positionY,positionZ\n");    
}

SimulationOutputCsv::~SimulationOutputCsv() = default;

// std::fixed pads every value out to the full precision, so a radius of 1
// goes over the wire as "1.000000000000". Those tail zeros carry no value
// and, at one row per particle per frame, they are a large share of the
// response — so drop them, along with a decimal point left with nothing
// after it. Trimming only ever removes digits that don't affect the value,
// so what the reader parses back is unchanged.
std::string trimTrailingZeros(std::string value) {
    if (value.find('.') == std::string::npos) {
        return value;
    }
    value.erase(value.find_last_not_of('0') + 1);
    if (value.back() == '.') {
        value.pop_back();
    }
    return value;
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 12)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return trimTrailingZeros(std::move(out).str());
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
