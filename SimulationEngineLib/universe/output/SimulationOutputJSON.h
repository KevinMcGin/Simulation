﻿#pragma once
#include "universe/output/SimulationOutput.h"

#include <vector>
#include <iostream>
#include <fstream>


class SimulationOutputJSON : public SimulationOutput {
public:
	SimulationOutputJSON(const char* outputFile);
	~SimulationOutputJSON();

	virtual void output(std::vector<Particle*> particles, unsigned long time);

private:
	std::ofstream myfile;
	std::string buffer = "{\n";
	const size_t maxBufferLength = 10000;
};