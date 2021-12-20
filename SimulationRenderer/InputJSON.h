#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace rapidjson;

// #include "Particle.cuh"
using namespace std;

class InputJSON {
public:
    InputJSON(const char* fileName);
	~InputJSON();
	Value* input();

private:
	Document doc;
	// vector<Particle*> particles;
	unsigned long time;
};