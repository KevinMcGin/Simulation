#include "SimulationOutputJSON.h"



SimulationOutputJSON::SimulationOutputJSON() : SimulationOutput()
{
	myfile.open("bin/simulation_output.json");
	myfile << "{" << endl;
}

SimulationOutputJSON::~SimulationOutputJSON()
{
	myfile << "}" << endl;
	myfile.close();
}

void SimulationOutputJSON::output(vector<Particle*> particles, unsigned long time)
{
	if (time > 0)
		myfile << "," << endl;
	myfile << "\"" << time << "\"" << ": [" << endl;
	unsigned int particleCount = particles.size();
	unsigned int i = 0;
	for (const auto& p : particles) {
		myfile << "{ ";
		myfile << "\"r\": " << p->radius << "," << endl;
		myfile << "\"pos\": [";
		myfile << p->position.x << ",";
		myfile << p->position.y << ",";
		myfile << p->position.z;
		myfile << "]}" << endl;
		if (++i < particleCount)
			myfile << "," << endl;

	}
	myfile << "]";
}
