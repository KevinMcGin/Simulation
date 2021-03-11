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
		for (vector<Particle*>::iterator it = particles.begin(); it != particles.end(); it++) {
			Particle* p2 = *it;
			if (p1 != p2) {
				if (collisionDetector->isCollision(p1, p2)) {
					collisionResolver->resolve(p1, p2);
					particles.erase(it);
					delete p2;
					goto start;
				}
			}
		}
}
