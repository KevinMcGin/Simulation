#pragma once
#include "util/Timing.h"

#include <map>

class UniverseTiming {
public:
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