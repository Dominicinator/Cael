#pragma once
#include "Particle.h"
namespace Cael
{
	class SimulationState
	{
	public:
		void initFromFile(const std::string & path);
		void initTwoBodyTest();
		void initRandomCartesian();

		std::vector<Particle> particles;

		SimulationState();
		virtual ~SimulationState();

		const double getTotalEnergy();
		//void updateEnergy(const Particle & particle, )
	};
}

