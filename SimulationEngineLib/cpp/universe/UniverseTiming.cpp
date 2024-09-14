#include "cpp/universe/UniverseTiming.h"
#include "util/Timing.h"

#include <cmath>
#include <iostream>
#include <map>

float round(float value, float accurary) {
	return std::round(value * accurary) / accurary;
}

UniverseTiming::UniverseTiming(unsigned long endTime) : 
	endTime(endTime) {}

void UniverseTiming::start() {
	timingTotal.setTime();
	progress = -1;
	timingSections.setTime();
}

void UniverseTiming::printPercentComplete(unsigned long time, bool force) {
	float fractionPassed = ((double)time) / endTime;
	progress = round(100 * fractionPassed, accurary);
	float elapsedSeconds = timingTotal.getTimeSeconds();
	if (force || elapsedSeconds - lastPrintedSeconds > maxTimeBetweenPrints) {
		lastPrintedSeconds = elapsedSeconds;
		float remainingPercent = 100 - progress;
		float timeRemaining = remainingPercent * ((elapsedSeconds-lastEstimatedSeconds) / (progress-lastEstimatedProgress));
		std::cout << "\r" << 
			"passed: " << progress << "% " << Timing::getTimeWithUnit(round(elapsedSeconds, accurary)) << ", "
			"remaining: " << remainingPercent << "% " << Timing::getTimeWithUnit(round(timeRemaining, accurary)) <<
			"                       " << std::flush;
	}
	if (elapsedSeconds - lastEstimatedSeconds >= minTimeBetweenEstimates) {
		lastEstimatedSeconds = elapsedSeconds;
		lastEstimatedProgress = progress;
	}
}


void UniverseTiming::updateSectionsTiming(std::string name) {
	if (progresses.find(name) == progresses.end()) {
		progresses[name] = 0;
	}
	progresses[name] += timingSections.getTimeSeconds();
	timingSections.setTime();
}

void UniverseTiming::printSectionsTiming() {
	std::string sections = "";
	for (auto const& it : progresses) {
		sections += it.first + ": " + Timing::getTimeWithUnit(it.second) + ", ";
	}
	std::cout << '\n' << sections << '\n';
}
