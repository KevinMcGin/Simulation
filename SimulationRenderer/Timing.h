#pragma once
#include <string>
#include <chrono>
using namespace std;

class Timing {
public:
    void setTime();
    float getTimeSeconds();
    string getTimeWithUnit();

private:
    chrono::high_resolution_clock::time_point startTime;
};