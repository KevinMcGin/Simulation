#pragma once
#include "cpp/universe/input/particleInput/field/ParticleInputField.h"

class ParticleInputFieldVelocityX : public ParticleInputField {
public:
    void set(Particle* particle, std::string value) override {
        particle->velocity.x = parseValue(value);
    }
    std::string getHeader() override { return "velocityX"; }
};