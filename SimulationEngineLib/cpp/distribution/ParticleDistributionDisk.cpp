#include "cpp/distribution/ParticleDistributionDisk.h"  
#include "cpp/particle/ParticleSimple.h"
#include "cpp/distribution/DistributionAnnulus.h"

	
ParticleDistributionDisk::ParticleDistributionDisk(
    std::shared_ptr<DistributionDensity> densityDistribution,
    float centralMass,
    Vector3D<float> meanPosition,
    float thetaPosition,
    float phiPosition,
    bool clockwise,
    std::shared_ptr<Distribution> innerRadius,
    std::shared_ptr<Distribution> outerRadius, 
    std::shared_ptr<Distribution> eccentricity,
    // std::shared_ptr<Distribution3D> angularVelocityDistribution,
    float positionBias,
    float G
) : densityDistribution(densityDistribution), centralMass(centralMass), meanPosition(meanPosition), thetaPosition(thetaPosition), phiPosition(phiPosition),
    clockwise(clockwise), innerRadius(innerRadius), outerRadius(outerRadius), eccentricity(eccentricity), 
    // angularVelocityDistribution(angularVelocityDistribution),
    positionBias(positionBias), G(G) { }
	
ParticleDistributionDisk::~ParticleDistributionDisk() = default;

Particle* ParticleDistributionDisk::getParticle() {
	float mass, radius;
	densityDistribution->getMassRadius(mass, radius);
    auto outerRadiusValue = outerRadius->getValue();
    auto innerRadiusValue = innerRadius->getValue();
    // The ring is sampled directly rather than by drawing from the whole
    // circle and rejecting anything inside the inner radius: rejection can
    // only ever produce an even spread, and it never terminates at all once
    // the inner radius reaches the outer one.
    DistributionAnnulus annulus(meanPosition, innerRadiusValue, outerRadiusValue, positionBias);
    Vector3D<float> position = annulus.getValue();
    Vector3D<float> difference = position - meanPosition;
    float differenceMagnitude = difference.magnitude();
    Vector3D<float> velocity;
    if (differenceMagnitude != 0) {
        float speed = sqrt( (G * centralMass) / differenceMagnitude);
        velocity = (clockwise ? -1 : 1) * speed * Vector3D<float>(0, 0, 1).crossProduct(difference).unit();
    } else {
        velocity = { 0.0, 0.0, 0.0 };
    }

	return new ParticleSimple(
        mass, 
        radius, 
        position, 
        velocity//, 
        // angularVelocityDistribution->getValue()
    );
}
