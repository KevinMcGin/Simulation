#pragma once
#include "cpp/universe/output/SimulationOutputFile.h"

#include <vector>
#include <iostream>
#include <fstream>


class SimulationOutputJson : public SimulationOutputFile {
public:
	SimulationOutputJson(const char* outputFile);
	~SimulationOutputJson();

	void output(std::vector<Particle*> particles, unsigned long time) override;
};
