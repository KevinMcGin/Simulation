#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

#include <iostream>
#include <sstream>
#include <string>

float ParticleInputField::parseValue(std::string value) {
    return std::stof(value);
}