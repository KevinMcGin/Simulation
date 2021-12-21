#include "Timing.h"
#include <sstream>

chrono::high_resolution_clock::time_point Timing::startTime;

void Timing::setTime() {
    Timing::startTime = chrono::high_resolution_clock::now();
}

float Timing::getTimeSeconds() {
    auto now = chrono::high_resolution_clock::now();
    double milliseconds = (now - Timing::startTime).count();
    return milliseconds/1000000000.0;
}

string Timing::getTimeWithUnit() {
    float seconds = Timing::getTimeSeconds();
    double time;
    string unit;
    if(seconds < 60) {
        time = seconds;
        unit = "s";
    } else if(seconds < 3600) {
        time = seconds / 60.0;
        unit = "mins";
    } else {
        time = seconds / 3600.0;
        unit = "hrs";
    }

    ostringstream secondsString;
    secondsString << time << unit;
    return secondsString.str();
}