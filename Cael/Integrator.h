#pragma once
#include "AccelerationFunction.h"
namespace Cael 
{
	enum Integrators { EULER, LEAPFROG };
	

	class Integrator
	{
	public:
		AccelerationFunction* accFunc;

		Integrator();
		virtual ~Integrator();
		virtual void update(SimulationState & state, Particle & particle, double & dt);
	};

	class EulerIntegrator : public Integrator
	{
	public:
		EulerIntegrator();
		virtual ~EulerIntegrator();
		void update(SimulationState & state, Particle & particle, double & dt);
	};

	class LeapFrogIntegrator : public Integrator
	{
	public:
		LeapFrogIntegrator();
		virtual ~LeapFrogIntegrator();
		void update(SimulationState & state, Particle & particle, double & dt);
	};

	Integrator* getIntegrator(Integrators integrator);
}


