#pragma once
#include "Integrator.h"
namespace Cael
{
	
	//enum InitialSimulationState { RANDOM_CARTESIAN, LOAD_FROM_FILE, PROTOPLANETARY_DISC, PLANETARY_DISTRIBUTION, GALACTIC_DISTRIBUTION};

	class Simulation
	{
	private:
		Integrator* integrator;
	public:
		void initialize();

		SimulationState initialState;
		SimulationState state;
		
		double deltaTime;
		
		Simulation();
		Simulation(Integrators integrator_, Methods method);
		virtual ~Simulation();

		void setIntegrator(Integrators integrator_);
		void setMethod(Methods method_);
		void restart();
		void step();
	};
}