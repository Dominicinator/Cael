#include "Integrator.h"

/*================================*/
//      VIRTUAL INTEGRATOR
/*================================*/
Cael::Integrator::Integrator() {}
Cael::Integrator::~Integrator() { delete accFunc; }
void Cael::Integrator::update(SimulationState & state, Particle & particle, double & dt) {}
/*================================*/
//   EXPLICIT EULER INTEGRATOR
/*================================*/
Cael::EulerIntegrator::EulerIntegrator() {}
Cael::EulerIntegrator::~EulerIntegrator() {}

void Cael::EulerIntegrator::update(SimulationState & state, Particle & particle, double & dt)
{
	particle.position += particle.velocity * dt;
	particle.velocity += accFunc->get(particle, state)*dt;
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
//   VELOCITY VERLET INTEGRATOR
/*================================*/
Cael::VelocityVerletIntegrator::VelocityVerletIntegrator() {}
Cael::VelocityVerletIntegrator::~VelocityVerletIntegrator() {}

void Cael::VelocityVerletIntegrator::update(SimulationState & state, Particle & particle, double & dt)
{
	//http://physics.ucsc.edu/~peter/242/leapfrog.pdf
	//v(n + 0.5) = vn + 0.5hF(x)
	vec2d vhalf = particle.velocity + accFunc->get(particle, state) * 0.5 * dt;
	//x(n+1) = xn + h*v(n+0.5)
	particle.position += vhalf * dt;
	//v(n+1) = v(n+0.5) + 0.5*h*F(x)
	particle.velocity = vhalf + accFunc->get(particle, state) * 0.5 * dt;
}
/*================================*/
//      INTEGRATOR SELECTOR
/*================================*/
Cael::Integrator* Cael::getIntegrator(Integrators integrator)
{
	if (integrator == Cael::EXPLICIT_EULER)
	{
		return new Cael::EulerIntegrator();
	}
	else if (integrator == Cael::LEAPFROG)
	{
		return new Cael::LeapFrogIntegrator();
	}
	else if (integrator == Cael::VELOCITY_VERLET)
	{
		return new Cael::VelocityVerletIntegrator();
	}
	else {
		return new Cael::EulerIntegrator();
	}
}
