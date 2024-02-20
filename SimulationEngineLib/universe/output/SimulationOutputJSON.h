#pragma once
#include "universe/output/SimulationOutputFile.h"

#include <vector>
#include <iostream>
#include <fstream>


class SimulationOutputJSON : public SimulationOutputFile {
public:
	SimulationOutputJSON(const char* outputFile);
	~SimulationOutputJSON();

	void output(std::vector<Particle*> particles, unsigned long time) override;
};
