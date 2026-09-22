#pragma once
#include "cpp/constant/PhysicalConstants.h"

#include <string>
#include <vector>

// Which momentum model the laws share. The Newtonian p = mv holds well
// below light speed; the Einsteinian one is what keeps a simulation honest
// once particles get relativistic.
enum MomentumModel {
	MOMENTUM_NEWTON,
	MOMENTUM_EINSTEIN
};

// Which laws a run applies, and the settings those laws take.
//
// Laws are named after the implementation, not the concept it implements:
// "collisionCoalesce" rather than "collision", "newtonGravity" rather than
// "gravity". Coalescing is one way to resolve a collision and Newton's is
// one model of gravity, so the concept names would have to be taken away
// from these the moment a second implementation of either arrives.
//
// The defaults reproduce exactly the fixed set the engine ran before any of
// this was configurable, so a caller that says nothing about laws gets the
// old behaviour rather than an empty universe.
struct LawConfig {
	bool isCollisionCoalesceEnabled = true;
	bool isNewtonGravityEnabled = true;
	bool isNewtonFirstLawEnabled = true;
	MomentumModel momentum = MOMENTUM_NEWTON;
	float gravitationalConstant = (float)PhysicalConstants::GRAVITATIONAL_CONSTANT;

	// The law names setLaws accepts, in the order the laws run.
	static const std::vector<std::string>& lawNames();

	// The momentum names setMomentum accepts.
	static const std::vector<std::string>& momentumNames();

	// Parses a comma-separated law list ("newtonGravity,newtonFirstLaw"), enabling
	// exactly the laws named and disabling every other one. An empty list is
	// a legitimate request for a universe with no laws at all — particles
	// frozen where they started — rather than an error.
	//
	// Returns an empty string on success, or a message naming what was
	// wrong. Nothing is applied unless the whole list parses, so a typo in
	// the last name can't leave a half-configured run behind.
	std::string setLaws(const std::string& laws);

	// Parses "newton" or "einstein".
	std::string setMomentum(const std::string& momentumName);

	// Parses NewtonGravity's gravitational constant. Rejected at zero and
	// below: it is multiplied into every pairwise force, so a zero silently
	// turns the law into an expensive no-op and a negative one inverts it.
	std::string setGravitationalConstant(const std::string& value);
};
