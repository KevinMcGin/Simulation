#include "Timing.h"
#include <sstream>

chrono::high_resolution_clock::time_point Timing::startTime;

void Timing::setTime() {
    Timing::startTime = chrono::high_resolution_clock::now();
}

string Timing::getTime() {
    auto now = chrono::high_resolution_clock::now();
    double milliseconds = (now - Timing::startTime).count();
    double seconds = milliseconds/1000000000.0;
    ostringstream secondsString;
    secondsString << seconds << "s";
    return secondsString.str();
}