#pragma once
#include "SimulationOutput.h"

#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class SimulationOutputJSON : public SimulationOutput {
public:
	SimulationOutputJSON() : SimulationOutput() {
		myfile.open("bin/simulation_output.json");
		myfile << "{" << endl;
	}
	~SimulationOutputJSON() {
		myfile << "}" << endl;
		myfile.close();
	}

	virtual void output(vector<Particle*> particles, unsigned long time) {
		if(time > 0)
			myfile << "," << endl;
		myfile << "\"" << time << "\"" << ": [" << endl;
		unsigned int particleCount = particles.size();
		unsigned int i = 0;
		for (const auto& p : particles) {
			myfile << "{ ";
			myfile << "\"r\": " << p->radius << "," << endl;
			myfile << "\"pos\": [";
			for (int i = 0; i < 3; i++) {
				myfile << p->position[i];
				if (i < 2)
					myfile << ",";
			}
			myfile << "]}" << endl;
			if (++i < particleCount)
				myfile << "," << endl;

		}
		myfile << "]";
	};

private:
	ofstream myfile;
};