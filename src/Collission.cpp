#include "Collission.h"

Collission::Collission(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver): Law(),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver)
{

}

void Collission::run(vector<Particle*>& particles)
{
	for (const auto& p1 : particles)
		for (const auto& p2 : particles) {
			if (p1 != p2 && p2 != NULL) {
				if (collisionDetector->isCollision(p1, p2)) {
					collisionResolver->resolve(p1, p2, particles);
				}
			}
		}
}
