#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "json.h"

// #include "Particle.cuh"
using namespace std;

class InputJSON {
public:
    InputJSON(string fileName);
	~InputJSON();
	void input();

private:
	Json::Value root;
	// vector<Particle*> particles;
	unsigned long time;
};