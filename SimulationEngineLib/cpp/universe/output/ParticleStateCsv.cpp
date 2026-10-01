#include "cpp/universe/output/ParticleStateCsv.h"
#include "cpp/util/CsvNumber.h"

const char* ParticleStateCsv::header =
    "mass,radius,positionX,positionY,positionZ,velocityX,velocityY,velocityZ";

std::string ParticleStateCsv::render(const std::vector<Particle*>& particles) {
    std::string csv = header;
    csv += "\n";

    for (const auto& p : particles) {
        const double cells[] = {
            p->mass,
            p->radius,
            p->position.x,
            p->position.y,
            p->position.z,
            p->velocity.x,
            p->velocity.y,
            p->velocity.z,
        };
        for (std::size_t i = 0; i < sizeof(cells) / sizeof(cells[0]); i++) {
            if (i > 0) {
                csv += ",";
            }
            csv += CsvNumber::format(cells[i]);
        }
        csv += "\n";
    }

    return csv;
}
