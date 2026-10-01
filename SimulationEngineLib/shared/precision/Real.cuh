#pragma once

// The precision every physical quantity in the simulation is carried at:
// masses, radii, positions, velocities, times and the constants that act on
// them.
//
// One alias rather than a type spelled out in two hundred places, so the
// choice can be revisited by editing a line. It is not merely tidiness —
// the choice is a real trade-off, and it is made here:
//
// `double`, because the simulation is meant to hold the real solar system.
// A body's position is measured from the solar system barycentre, so
// resolving a moon means resolving its orbit as a difference between two
// much larger numbers. Phobos orbits 9,376 km from a Mars that is itself
// 2.3e11 m out: at `float`, where the gap between representable values at
// that distance is about 14 km, that orbit is quantised to roughly a part
// in six hundred, every step, accumulating. At `double` it is not close to
// a concern.
//
// The cost is real and falls on the GPU: a Particle is twice the size on
// the device, and double-precision arithmetic is several times slower on
// consumer hardware than single. That is the price of the solar system
// being representable at all.
using Real = double;
