#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldPositionX : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->position.x = parseValue(value);
    }
    std::string getHeader() override { return "positionX"; }
};