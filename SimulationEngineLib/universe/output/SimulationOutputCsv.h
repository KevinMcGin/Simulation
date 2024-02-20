#pragma once
#include "universe/output/SimulationOutputFile.h"

#include <vector>
#include <iostream>
#include <fstream>


class SimulationOutputCsv : public SimulationOutputFile {
public:
	SimulationOutputCsv(const char* outputFile);
	~SimulationOutputCsv();

	void output(std::vector<Particle*> particles, unsigned long time) override;
};
