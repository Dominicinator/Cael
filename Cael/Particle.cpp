#include "Particle.h"

namespace Cael
{
	Particle::Particle()
	{
	}

	Particle::Particle(const vec2d & position, const vec2d & velocity, const double & mass, const double & density)
		: position(position), velocity(velocity), mass(mass), density(density), radius(std::cbrt((3 / (4 * 3.14159265358979323846)) * mass / density)) {}


	Particle::~Particle()
	{
	}
}

