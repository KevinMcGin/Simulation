#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "lib/json/json.h"

// #include "Particle.cuh"
using namespace std;

class InputJSON {
public:
    InputJSON(string fileName);
	~InputJSON();
	Json::Value input();

private:
	Json::Value root;
	// vector<Particle*> particles;
	unsigned long time;
};