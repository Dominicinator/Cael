#pragma once
#include "AccelerationFunction.h"
namespace Cael 
{
	enum Integrators { EXPLICIT_EULER, LEAPFROG, VELOCITY_VERLET };
	

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
	class VelocityVerletIntegrator : public Integrator
	{
	public:
		VelocityVerletIntegrator();
		virtual ~VelocityVerletIntegrator();
		void update(SimulationState & state, Particle & particle, double & dt);
	};

	Integrator* getIntegrator(Integrators integrator);
}


