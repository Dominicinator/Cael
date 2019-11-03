#include "AccelerationFunction.h"
/*================================*/
//  VIRTUAL ACCELERATION FUNCTION
/*================================*/
Cael::AccelerationFunction::AccelerationFunction() {}
Cael::AccelerationFunction::~AccelerationFunction() {}
void Cael::AccelerationFunction::frameinit(const SimulationState & state) { std::cout << "frameinit virtual" << std::endl; }
Cael::vec2d Cael::AccelerationFunction::get(const Particle & particle, const SimulationState & state){ return vec2d(); }
/*===================================*/
//   SQUARE ACCELERATION FUNCTION
/*===================================*/
Cael::SquareAccelerationFunction::SquareAccelerationFunction() {}
Cael::SquareAccelerationFunction::~SquareAccelerationFunction() {}
void Cael::SquareAccelerationFunction::frameinit(const SimulationState & state)
{
	std::cout << "frameinit square" << std::endl;
}
Cael::vec2d Cael::SquareAccelerationFunction::get(const Particle & particle, const SimulationState & state)
{
	vec2d acceleration(0.0, 0.0);
	for (auto & p : state.particles)
	{
		if (!(&p == &particle))
		{
			//vec2d distanceVector = (p.position - particle.position);
			acceleration += (p.position - particle.position).normalized()*(Cael::Utility::Units::G*p.mass) / ((p.position - particle.position).squaredNorm());
		}
	}
	return acceleration;
}
/*===================================*/
//DISTANCE MATRIX ACCELERATION FUNCTION
/*===================================*/

//frameinit -> fill distance matrix
//get -> use distance matrix to do yeah

/*================================*/
//BARNES-HUT ACCELERATION FUNCTION
/*================================*/
Cael::BarnesHutAccelerationFunction::BarnesHutAccelerationFunction() {}
Cael::BarnesHutAccelerationFunction::~BarnesHutAccelerationFunction() {}
void Cael::BarnesHutAccelerationFunction::frameinit(const SimulationState & state)
{
	//fill tree
}

Cael::vec2d Cael::BarnesHutAccelerationFunction::get(const Particle & particle, const SimulationState & state)
{
	//calculate acceleration using tree
	return vec2d();
}


