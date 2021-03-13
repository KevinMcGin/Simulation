#pragma once
#include <string>
#include <chrono>
using namespace std;

class Timing {
public:
    static void setTime();
    static string getTime();

private:
    static chrono::high_resolution_clock::time_point startTime;
};