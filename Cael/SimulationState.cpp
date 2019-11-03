#include "SimulationState.h"
#include <fstream>
#include <sstream>
#include <iostream>

Cael::SimulationState::SimulationState() {}

Cael::SimulationState::~SimulationState() {}

void Cael::SimulationState::initFromFile(const std::string & path)
{
	//std::vector<Particle> inputParticles;
	std::string line;
	std::ifstream filestream(path);
	while (getline(filestream, line))
	{
		std::istringstream is(line);
		std::string name;
		double mass;
		double density;
		double posx, posy;
		double velx, vely;
		is >> name >> mass >> density >> posx >> posy >> velx >> vely;
		if (is.fail())
		{
			std::cout << "failed to read from file";
		}
		particles.push_back(Particle(vec2d(posx, posy), vec2d(velx, vely), mass, density));
	}
	//particles.reserve(inputParticles.size())
	//for (int i = 0; i < particles.size(); ++i)
	//{
	//	particles.set(i, inputParticles[i]);
	//}
}


