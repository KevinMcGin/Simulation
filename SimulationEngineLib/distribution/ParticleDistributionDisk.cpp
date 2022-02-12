#include "distribution/ParticleDistributionDisk.h"  
#include "particle/ParticleSimple.h"
#include "distribution/DistributionCircle.h"
	
ParticleDistributionDisk::ParticleDistributionDisk(
    std::shared_ptr<DistributionDensity> densityDistribution,
    double centralMass,
    Vector3D meanPosition,
    double thetaPosition,
    double phiPosition,
    bool clockwise,
    std::shared_ptr<Distribution> innerRadius,
    std::shared_ptr<Distribution> outerRadius, 
    std::shared_ptr<Distribution> eccentricity,
    // std::shared_ptr<Distribution3D> angularVelocityDistribution,
    double G
) : densityDistribution(densityDistribution), centralMass(centralMass), meanPosition(meanPosition), thetaPosition(thetaPosition), phiPosition(phiPosition),
    clockwise(clockwise), innerRadius(innerRadius), outerRadius(outerRadius), eccentricity(eccentricity), 
    // angularVelocityDistribution(angularVelocityDistribution),
    G(G) { }
	
ParticleDistributionDisk::~ParticleDistributionDisk() = default;

Particle* ParticleDistributionDisk::getParticle() {
	double mass, radius;
	densityDistribution->getMassRadius(mass, radius);
    DistributionCircle circle(meanPosition, outerRadius->getValue());
    Vector3D position = circle.getValue();
    Vector3D difference = position - meanPosition;
    double differenceMagnitude = difference.magnitude();
    Vector3D velocity;
    if(differenceMagnitude != 0) {
        double speed = sqrt( (G * centralMass) / differenceMagnitude);
        velocity = (clockwise ? -1 : 1) * speed * Vector3D(0, 0, 1).crossProduct(difference).unit();
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
