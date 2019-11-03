#pragma once
#include "Particle.h"
namespace Cael
{
	class SimulationState
	{
	private:

	public:
		void initFromFile(const std::string & path);
		void initRandomCartesian();

		std::vector<Particle> particles;

		SimulationState();
		virtual ~SimulationState();
	};
}

