#include "util/Timing.h"
#include <sstream>

void Timing::setTime() {
    startTime = std::chrono::high_resolution_clock::now();
}

float Timing::getTimeSeconds() {
    auto now = std::chrono::high_resolution_clock::now();
    float milliseconds = (float)(now - startTime).count();
    return milliseconds/1000000000.0;
}


std::string Timing::getTimeWithUnit(float seconds) {
    float time;
    std::string unit;
    if(seconds < 60) {
        time = seconds;
        unit = "s";
    } else if(seconds < 3600) {
        time = seconds / 60.0;
        unit = " mins";
    } else {
        time = seconds / 3600.0;
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