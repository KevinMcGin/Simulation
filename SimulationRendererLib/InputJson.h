#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace rapidjson;

// #include "shared/particle/Particle.cuh"


class InputJson {
public:
    InputJson(const char* fileName);
	~InputJson();
	Value* input(int elapsedFrames);

private:
	Document doc;
	// std::vector<Particle*> particles;
	unsigned long time;
	unsigned long originalTime;

	Value* getFrame();
	Value* getLastFrame();
};