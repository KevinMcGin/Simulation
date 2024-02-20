#include <string>

#include "universe/output/SimulationOutputFile.h"

SimulationOutputFile::SimulationOutputFile(const char* outputFile) : SimulationOutput() {
    myfile.open(outputFile);
}

SimulationOutputFile::~SimulationOutputFile() {
    myfile << buffer << std::endl;
	myfile.close();
}

void SimulationOutputFile::writeToBufferMaybe() {
	auto bufferLength = buffer.length();
	if (bufferLength >= maxBufferLength) {
		myfile << buffer;
		buffer = "";
	}
}

void SimulationOutputFile::appendToBuffer(std::string stringToAppend) {
    buffer = buffer.append(stringToAppend);
}
