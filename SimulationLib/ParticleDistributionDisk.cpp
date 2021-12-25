#include "ParticleDistributionDisk.h"  
#include "ParticleSimple.h"
#include "DistributionCircle.h"
	
ParticleDistributionDisk::ParticleDistributionDisk(
    shared_ptr<DistributionDensity> densityDistribution,
    double centralMass,
    Vector3D meanPosition,
    double thetaPosition,
    double phiPosition,
    bool clockwise,
    double innerRadius,
    double outerRadius, 
    double eccentricity,
    shared_ptr<Distribution3D> angularVelocityDistribution,
    double G
) : densityDistribution(densityDistribution), centralMass(centralMass), meanPosition(meanPosition), thetaPosition(thetaPosition), phiPosition(phiPosition),
    clockwise(clockwise), innerRadius(innerRadius), outerRadius(outerRadius), eccentricity(eccentricity), angularVelocityDistribution(angularVelocityDistribution),
    G(G)
{
	
}
	
ParticleDistributionDisk::~ParticleDistributionDisk()
{
	
}

Particle* ParticleDistributionDisk::getParticle()
{
	double mass, radius;
	densityDistribution->getMassRadius(mass, radius);
    DistributionCircle circle(meanPosition, outerRadius);
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
        mass, radius, 
        position, velocity, 
        angularVelocityDistribution->getValue()
    );
}
