#pragma once
#include "universe/output/SimulationOutput.h"

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class SimulationOutputJSON : public SimulationOutput {
public:
	SimulationOutputJSON(const char* outputFile);
	~SimulationOutputJSON();

	virtual void output(vector<Particle*> particles, unsigned long time);

private:
	ofstream myfile;
	string buffer = "{\n";
	const size_t maxBufferLength = 10000;
};