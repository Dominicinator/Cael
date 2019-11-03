#pragma once
#include "Utility.h"
#include "SimulationState.h"
#include "BarnesHutTree.h"
#include <iostream>
namespace Cael 
{
	enum Methods { SQUARE, BARNESHUT };
	class AccelerationFunction
	{
	public:
		AccelerationFunction();
		virtual ~AccelerationFunction();
		virtual void frameinit(const SimulationState & state);
		virtual vec2d get(const Particle & particle, const SimulationState & state);
	};
	class SquareAccelerationFunction : public AccelerationFunction
	{
	public:
		SquareAccelerationFunction();
		virtual ~SquareAccelerationFunction();
		void frameinit(const SimulationState & state);
		vec2d get(const Particle & particle, const SimulationState & state);
	};
	class DistanceMatrixAccelerationFunction : public AccelerationFunction
	{

	};
	class BarnesHutAccelerationFunction : public AccelerationFunction
	{
	public:
		BarnesHutAccelerationFunction();
		virtual ~BarnesHutAccelerationFunction();
		void frameinit(const SimulationState & state);
		vec2d get(const Particle & particle, const SimulationState & state);
	};

	AccelerationFunction* getAccelerationFunction(const Methods & method);
}


