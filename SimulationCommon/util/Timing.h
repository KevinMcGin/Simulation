#pragma once
#include <string>
#include <chrono>


class Timing {
public:
    void setTime();
    float getTimeSeconds() const;
    std::string getTimeWithUnit();
    static std::string getTimeWithUnit(float seconds);

private:
    std::chrono::high_resolution_clock::time_point startTime;
};