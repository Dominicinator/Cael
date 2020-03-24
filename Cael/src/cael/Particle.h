#pragma once
#include "Utility.h"
namespace Cael
{
	class Particle
	{
	public:
		/*STATE PROPERTIES*/

		vec2d position;
		vec2d velocity;

		//vec2d acceleration;

		/*PROPERTIES*/
		double mass;
		double density;
		double radius;

		Particle();
		Particle(const vec2d & position, const vec2d & velocity, const double & mass, const double & density);
		virtual ~Particle();
	};
}