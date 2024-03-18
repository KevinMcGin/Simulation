#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

float ParticleInputField::parseValue(std::string value) {
    return std::stof(value);
}