#include "Collision.h"
#include <map>
#include <algorithm>
#include <iterator>
#include <set>


Collision::Collision(CollisionDetector* collisionDetector, CollisionResolver* collisionResolver): Law("Collision"),
	collisionDetector(collisionDetector),
	collisionResolver(collisionResolver) {
		
}

void Collision::cpuRun(vector<Particle*>& particles)
{
	// get particles that collided
	vector<set<Particle*>*> particlesCollidedVector;
	for (auto it1 = particles.begin(); it1 != particles.end(); it1++) {
		auto p1 = *it1;
    	set<Particle*> particlesCollidedSet = {};
		for (auto it2 = it1+1; it2 < particles.end(); it2++) {
			auto p2 = *it2;
			if (collisionDetector->isCollision(p1, p2)) {
				particlesCollidedSet.insert(p1);
				particlesCollidedSet.insert(p2);
			}
		}
		if(particlesCollidedSet.size() > 0)
			particlesCollidedVector.push_back(new set<Particle*>(particlesCollidedSet));
	}
	// merge sets of particles that collided
	for (auto it1 = particlesCollidedVector.begin(); it1 != particlesCollidedVector.end(); it1++) {
		auto particlesCollided1 = *it1;
		for (auto it2 = it1+1; it2 < particlesCollidedVector.end(); it2++) {
			auto particlesCollided2 = *it2;
			if ([&]() {
				for(auto p: *particlesCollided2) {
					if(particlesCollided1->find(p) != particlesCollided1->end()) {
						return true;
					}
				}
				return false;
			}()) {
				for(auto p: *particlesCollided2) {
					particlesCollided1->insert(p);
				}
				particlesCollided2->clear();
			}
		}
	}
	//resolve particles
	for (auto particlesCollided1: particlesCollidedVector) {
		if(particlesCollided1->size() > 0) {
			auto p1 = *(particlesCollided1->begin());
			particlesCollided1->erase(particlesCollided1->begin());
			for(auto p2: *particlesCollided1) {
				collisionResolver->resolve(p1, p2);
			}
		}
	}
	//erase particles marked for deletion safely
	for (auto it = particles.begin(); it != particles.end();) {
		if((*it)->deleted) {
			delete *it;
			it = particles.erase(it);
		}
		else
			++it;
	}
}


void Collision::gpuRun(vector<Particle*>& particles) {
	//TODO: implement parallel version
	cpuRun(particles);
}