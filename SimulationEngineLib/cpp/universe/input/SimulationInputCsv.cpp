#include "cpp/universe/input/SimulationInputCsv.h"
#include <sstream>

std::vector<std::string> split(const std::string& s, char delimiter)                                                                                                                          
{                                                                                                                                                                                             
   std::vector<std::string> splits;                                                                                                                                                           
   std::string split;                                                                                                                                                                         
   std::istringstream ss(s);                                                                                                                                                                  
   while (std::getline(ss, split, delimiter))                                                                                                                                                 
   {                                                                                                                                                                                          
      splits.push_back(split);                                                                                                                                                                
   }                                                                                                                                                                                          
   return splits;                                                                                                                                                                             
}


SimulationInputCsv::SimulationInputCsv(const char* fileName) :
	SimulationInputFile(fileName) {
		//Get headers as list of string of split by comma from first line in file
		std::string line;
    	if (file.is_open()) {
			std::getline(file, line, '\n');
		}
		std::vector<std::string> headers = split(line, ',');
		particleInput = new ParticleInput(headers);
	}

SimulationInputCsv::~SimulationInputCsv() {
	if (file.is_open()) {
		file.close();
	}
}


std::vector<Particle*> SimulationInputCsv::input() {
	std::vector<Particle*> particles;
	std::string line;
	while (!file.eof()) {
		std::getline(file, line, '\n');
		//Todo: Particle type created depends on headers available
		ParticleSimple* particle = new ParticleSimple(
			0, 0, { 0, 0, 0, }, { 0, 0, 0, }
		);
		std::vector<std::string> values = split(line, ',');
		particleInput->set(particle, values);
		particles.push_back(particle);
	}
	return particles;
}
