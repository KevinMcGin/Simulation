#include <string>

#include "universe/output/SimulationOutputFile.h"

SimulationOutputFile::SimulationOutputCsv(const char* outputFile) : SimulationOutput() {
    myfile.open(outputFile);
}

SimulationOutputFile::~SimulationOutputCsv() {
    myfile << buffer << std::endl;
	myfile.close();
}

void SimulationOutputFile::writeBuffer() {
	auto bufferLength = buffer.length();
	if (bufferLength >= maxBufferLength) {
		myfile << buffer;
		buffer = "";
	}
}

void SimulationOutputFile::appendToBuffer(std::string stringToAppend) {
    buffer = buffer.append(stringToAppend);
}
