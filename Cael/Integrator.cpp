#include "Integrator.h"

/*================================*/
//      VIRTUAL INTEGRATOR
/*================================*/
Cael::Integrator::Integrator() {}
Cael::Integrator::~Integrator() { delete accFunc; }
void Cael::Integrator::update(SimulationState & state, Particle & particle, double & dt) {}
/*================================*/
//   (FORWARD) EULER INTEGRATOR
/*================================*/
Cael::EulerIntegrator::EulerIntegrator() {}
Cael::EulerIntegrator::~EulerIntegrator() {}

void Cael::EulerIntegrator::update(SimulationState & state, Particle & particle, double & dt)
{
	particle.position += particle.velocity * dt;
	particle.velocity += (*accFunc).get(particle, state)*dt;
}
/*================================*/
//      LEAPFROG INTEGRATOR
/*================================*/
Cael::LeapFrogIntegrator::LeapFrogIntegrator(){}
Cael::LeapFrogIntegrator::~LeapFrogIntegrator(){}

void Cael::LeapFrogIntegrator::update(SimulationState & state, Particle & particle, double & dt)
{
}
/*================================*/
//      INTEGRATOR SELECTOR
/*================================*/
Cael::Integrator* Cael::getIntegrator(Integrators integrator)
{
	if (integrator == Cael::EULER)
	{
		return new Cael::EulerIntegrator();
	}
	else if (integrator == Cael::LEAPFROG)
	{
		return new Cael::LeapFrogIntegrator();
	}
	else {
		return new Cael::EulerIntegrator();
	}
}