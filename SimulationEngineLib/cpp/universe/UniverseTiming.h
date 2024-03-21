#pragma once
#include "util/Timing.h"

#include <map>

class UniverseTiming {
public:
    UniverseTiming(unsigned long endTime);
    void start();
	void printPercentComplete(unsigned long time, bool force = false);
	void updateSectionsTiming(std::string name);
	void printSectionsTiming();    
private:
    unsigned long endTime;
    Timing timingTotal = Timing();
    Timing timingSections = Timing();
    std::map<std::string, float> progresses = {};
    
    const float maxTimeBetweenPrints = 0.8f;
    const float minTimeBetweenEstimates = 0.5f;
	const float accurary = 100.f;

	float progress;
    float lastPrintedSeconds = 0.f;
    float lastEstimatedSeconds = 0.f;
    float lastEstimatedProgress = 0.f;
};