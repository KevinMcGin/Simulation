#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

#include <iostream>
#include <sstream>
#include <string>

Real ParticleInputField::parseValue(std::string value) {
    return std::stod(value);
}