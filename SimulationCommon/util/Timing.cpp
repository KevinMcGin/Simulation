#include "util/Timing.h"
#include <sstream>

void Timing::setTime() {
    startTime = std::chrono::high_resolution_clock::now();
}

float Timing::getTimeSeconds() const {
    auto now = std::chrono::high_resolution_clock::now();
    auto milliseconds = (float)(now - startTime).count();
    return milliseconds/1000000000.f;
}


std::string Timing::getTimeWithUnit(float seconds) {
    float time;
    std::string unit;
    if (seconds < 60) {
        time = seconds;
        unit = "s";
    } else if (seconds < 3600) {
        time = seconds / 60.f;
        unit = " mins";
    } else {
        time = seconds / 3600.f;
        unit = " hrs";
    }

    std::ostringstream secondsString;
    secondsString << time << unit;
    return secondsString.str();
}


std::string Timing::getTimeWithUnit() {
    float seconds = getTimeSeconds();
    return Timing::getTimeWithUnit(seconds);
}