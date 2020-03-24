#include "SimulationState.h"
#include <fstream>
#include <sstream>
#include <iostream>

Cael::SimulationState::SimulationState() {}

Cael::SimulationState::~SimulationState() {}

const double Cael::SimulationState::getTotalEnergy()
{
	double kineticEnergy = 0;
	double potentialEnergy = 0;
	for (int i = 0; i < particles.size(); ++i)
	{
		for (int j = i + 1; j < particles.size(); ++j)
		{
			kineticEnergy += 0.5 * (particles[i].velocity.squaredNorm()*particles[i].mass + particles[j].velocity.squaredNorm()*particles[j].mass);
			double r = (particles[i].position - particles[j].position).norm();
			potentialEnergy -= 2 * Cael::Utility::Units::G * particles[i].mass * particles[j].mass / r;
			//potentialEnergy -= Cael::Utility::Units::G * (particles[i].mass + particles[j].mass) / r;
		}
	}
	return kineticEnergy + potentialEnergy;
}

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

void Cael::SimulationState::initTwoBodyTest()
{
	Particle a(vec2d(0.0, 0.0), vec2d(0.0, 0.0), 1.99e+30, 1400);
	a.radius *= 100;

	Particle b(vec2d(Cael::Utility::Units::AU, 0.0), vec2d(0.0, 29786.1), Cael::Utility::Units::EarthMasses, 5400.0);
	b.radius *= 300;
	particles.push_back(a);
	particles.push_back(b);
}


