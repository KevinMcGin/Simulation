#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldVelocityZ : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->velocity.z = parseValue(value);
    }
    std::string getHeader() override { return "velocityZ"; }
};