#pragma once
#include "universe/output/SimulationOutput.h"

#include <vector>
#include <iostream>
#include <fstream>


class SimulationOutputFile : public SimulationOutput {
public:
	SimulationOutputFile(const char* outputFile);
	virtual ~SimulationOutputFile();

	virtual void output(std::vector<Particle*> particles, unsigned long time) override = 0;

protected:
    void writeToBuffer();
    void writeToBufferMaybe();
    void appendToBuffer(std::string stringToAppend);

private:
	std::ofstream myfile;
	std::string buffer = "";  
	const size_t maxBufferLength = 10000;
};
