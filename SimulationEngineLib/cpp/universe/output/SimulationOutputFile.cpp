#include <string>

#include "cpp/universe/output/SimulationOutputFile.h"

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
		writeToBuffer();
	}
}

void SimulationOutputFile::writeToBuffer() {
	myfile << buffer;
	buffer = "";
}

void SimulationOutputFile::appendToBuffer(std::string stringToAppend) {
    buffer = buffer.append(stringToAppend);
}
