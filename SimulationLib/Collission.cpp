#include "Collission.h"

Collission::Collission(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver): Law(),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver)
{

}

void Collission::run(vector<Particle*>& particles)
{
	start:
	for (Particle* p1 : particles)
		for (vector<Particle*>::iterator it2 = particles.begin(); it2 != particles.end(); it2++) {
			Particle* p2 = *it2;
			if (p1 != p2) {
				if (collisionDetector->isCollision(p1, p2)) {
					collisionResolver->resolve(p1, it2, particles);
					goto start;
				}
			}
		}
}
