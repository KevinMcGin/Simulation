﻿#pragma once
#include "SimulationOutput.h"

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class SimulationOutputJSON : public SimulationOutput {
public:
	SimulationOutputJSON();
	~SimulationOutputJSON();

	virtual void output(vector<Particle*> particles, unsigned long time);

private:
	ofstream myfile;
};