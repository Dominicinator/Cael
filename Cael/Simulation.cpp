#include "Simulation.h"



void Cael::Simulation::initialize()
{
	state = initialState;
}

Cael::Simulation::Simulation() {}

Cael::Simulation::Simulation(Integrators integrator_, Methods method)
	: integrator(Cael::getIntegrator(integrator_))
{
}


Cael::Simulation::~Simulation()
{
}

void Cael::Simulation::setIntegrator(Integrators integrator_)
{
	delete integrator;
	integrator = Cael::getIntegrator(integrator_);
}

void Cael::Simulation::setMethod(Methods method_)
{
	delete integrator->accFunc;
	if (method_ == SQUARE)
	{
		integrator->accFunc = new SquareAccelerationFunction();
	}
}

void Cael::Simulation::restart()
{
	state = initialState;
}

void Cael::Simulation::step()
{
	integrator->accFunc->frameinit(state);
	for (int i = 0; i < state.particles.size(); ++i)
	{
		integrator->update(state, state.particles[i], deltaTime);
	}
}
