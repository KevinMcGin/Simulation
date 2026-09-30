#include "cpp/universe/input/particleInput/ParticleInput.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldMass.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldRadius.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionX.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionY.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldPositionZ.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityX.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityY.h"
#include "cpp/universe/input/particleInput/field/ParticleInputFieldVelocityZ.h"

ParticleInput::ParticleInput(std::vector<std::string> headers) :
    inputsInUse({}) {

    inputsAvailable.push_back(std::make_unique<ParticleInputFieldMass>());
    inputsAvailable.push_back(std::make_unique<ParticleInputFieldRadius>());
    inputsAvailable.push_back(std::make_unique<ParticleInputFieldPositionX>());
    inputsAvailable.push_back(std::make_unique<ParticleInputFieldPositionY>());
    inputsAvailable.push_back(std::make_unique<ParticleInputFieldPositionZ>());
    inputsAvailable.push_back(std::make_unique<ParticleInputFieldVelocityX>());
    inputsAvailable.push_back(std::make_unique<ParticleInputFieldVelocityY>());
    inputsAvailable.push_back(std::make_unique<ParticleInputFieldVelocityZ>());

    for (const auto& header : headers) {
        ParticleInputField* input = findInputField(header);
        if (input != nullptr) {
            inputsInUse.push_back(input);
        } else {
            throw std::invalid_argument("ParticleInput: Header not found");
        }
    }
}

void ParticleInput::set(Particle* particle, std::vector<std::string> values) {
    if (values.size() > inputsInUse.size()) {
        throw std::invalid_argument("ParticleInput: Too many values for headers");
    }
    for (int i = 0; i < values.size(); i++) {
        inputsInUse[i]->set(particle, values[i]);
    }
}

ParticleInputField* ParticleInput::findInputField(std::string header) {
    for (const auto& input : inputsAvailable) {
        if (input->getHeader() == header) {
            return input.get();
        }
    }
    return nullptr;
}
