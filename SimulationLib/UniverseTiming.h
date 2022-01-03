#pragma once
#include "Timing.h"

#include <map>

class UniverseTiming {
public:
    Timing timingTotal = Timing();
    Timing timingSections = Timing();
    map<string, float> progresses = {};
	double progress;
    const float maxTimeBetweenPrints = 0.8f;
    const float maxTimeBetweenEstimates = 5.f;
    float lastPrintedSeconds = 0.f;
    float lastEstimatedSeconds = 0.f;
    float lastEstimatedProgress = 0.f;
};