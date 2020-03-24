#include "Simulation.h"



void Cael::Simulation::initialize()
{
	state = initialState;
	initialEnergy = initialState.getTotalEnergy();
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
	integrator->accFunc = Cael::getAccelerationFunction(method_);
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

Cael::SimulationState Cael::Simulation::stepState()
{
	step();
	return state;
}

void Cael::Simulation::runSteps(std::vector<SimulationState>& states, const unsigned int & nSteps, const double & dt)
{
	double tempdt = deltaTime;
	deltaTime = dt;
	states.reserve(nSteps);
	for (unsigned int i = 0; i < nSteps; ++i)
	{
		states.push_back(stepState());
	}
	restart();
	deltaTime = tempdt;
}

void Cael::Simulation::runPeriod(std::vector<SimulationState> & states, const double & timeLength, const unsigned int & nSteps)
{
	runSteps(states, nSteps, timeLength / nSteps);
}

double Cael::Simulation::getEnergyError()
{
	return ((state.getTotalEnergy() - initialEnergy) / initialEnergy) * 100;
}
