#pragma once
#include <string>

// How every number the engine writes into a CSV is rendered. Shared so the
// animation output and the final-state output cannot drift into formatting
// the same value two different ways.
namespace CsvNumber {
    std::string format(double value);
}
