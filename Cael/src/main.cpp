#include <SFML/Graphics.hpp>
#include "../World.h"
#include <iostream>
//world object should have dimension

/*
//TODO:
	SimulationStateStepper superclass to wrap integrators? Can use it to define behaviour like calculating energy easier (ie integrate it into accelerationfunction calculation and stuff like that so it doesnt affect performance as much)
	SimulationState init functions should be moved to simulation
	frameinit in AccelerationFunction should be called stepinit or initialize or something
	setIntegrator and setMethod should also be able to take in Integrator and AccelerationFunction objects as parameters.
	SimulationState should be a superclass? maybe stuff like SimulationStateBenchmark which keeps track of extra variables like accuracy and energy error, then SimulationStateStepperBenchmark could define that data's behaviour.
	Particle should be a superclass, and it should be templated to be N-dimensional (probably 2 and 3 specifically lol)
	Cael::SpatialTrees namespace which contains the SpatialTree superclass, which is templated to be N-dimensional; similarly with the SpatialNode superclass; then define something like BarnesHutTree : SpatialTree and BarnesHutNode : Node
	SpatialTree class should implement getExternalNode(N-dim position) to get the lowest external node of the tree at that position (use for click detection and maybe collision detection and stuff)
	move Integrator, Simulation, SimulationState, Particle, and AccelerationFunction in Cael::Physics namespace (or maybe call it Cael::Simulation? but same name as class so)
	change Cael::Utility::Units to just Cael::Units
	move World to Cael::Visualization
	Could move calls to simulation.step to a different loop which is independant of the renderloop so that deltatime is stable relative to framerate (will be out of sync with renderloop probably, so just display last calculated SimulationState)
	Implement runbenchmark function in Cael namespace to run a benchmark of a method or list of methods, then display a graph to compare them (maybe several graphs of different situations, ie circular orbit, elliptical orbit, random, different starting momenta, etc.)
	Implement particle rotation, angular momentum, collision...

	Collision:
		Do it like I did before where a list of collisions is collected every step and they are all handled at the same time at the end of the step
		could later implement actual simulation of the collision... somehow, look up how to do it, look at SPH maybe? greenleaf
	
	Solar system formation
		should implement a way to handle particles with different rules; ie some particles shouldnt contribute to total N-body force (ie rings and stuff maybe)
		Star formation with radiation pressure calculation to drive density changes in protoplanetary discs
		research number of particles needed for good simulation
		find ways to do it real fast
	implement way to do solar system formation out of various materials, (ie make Planet or Body a subclass of particle with more complex data like composition and temperature)
	add ui and stuff to Cael::Visualization
	implement keplerian stuff, maybe patched conics

	//https://www.youtube.com/watch?v=IJ2MhXUDZ6o
	//https://arxiv.org/pdf/cond-mat/0110585.pdf
	//http://physics.ucsc.edu/~peter/242/leapfrog.pdf
	//https://math.stackexchange.com/questions/234263/procedure-for-adaptive-step-size-for-runge-kutta-4
	//https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods
	//https://scicomp.stackexchange.com/questions/19020/applying-the-runge-kutta-method-to-second-order-odes
	//https://www.youtube.com/watch?v=qKp1M4T6z24
	//https://www.youtube.com/watch?v=MHrUeGV1DtM
	//https://www.youtube.com/watch?v=2kQls0t-tCU
*/
int main()
{
	//Cael::
	//Cael::Simulation simulation;
	World world;
	/*
	world.simulation.initialState.initFromFile("resources/solarsystem.txt");
	world.simulation.setIntegrator(Cael::EULER);
	world.simulation.setMethod(Cael::SQUARE);
	world.simulation.initialize();
	world.simulation.deltaTime = 20.0;
	world.scale = 1e-6;
	world.camera.followIndex = 1;
	*/
	//world.simulation.initialState.initTwoBodyTest();
	world.simulation.initialState.initFromFile("resources/solarsystem.txt");
	world.simulation.setIntegrator(Cael::VELOCITY_VERLET);
	world.simulation.setMethod(Cael::SQUARE);
	world.simulation.initialize();
	world.simulation.deltaTime = Cael::Utility::Units::minute;
	world.scale = 1e-6;
	world.camera.followIndex = 1;
	//double initialEnergy = world.simulation.state.getTotalEnergy();
	//std::cin.get();
	//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!");
	sf::Font font;
	sf::Text energyError;
	energyError.setFont(font);
	energyError.setFillColor(sf::Color::Cyan);
	energyError.setCharacterSize(24);
	if (!font.loadFromFile("resources/fonts/arial_narrow_7.ttf"))
	{
		std::cout << "Failed to load font\n";
	}
	
	sf::RenderWindow window(sf::VideoMode(800, 800), "Cael");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			world.handleEvent(event, window);
		}
		world.simulation.step();
		world.update(window); //note: world update needs to happen after simulation step to avoid desync with simulation and camera position and stuff like that
		energyError.setString(std::to_string(world.simulation.getEnergyError()) + "%");
		//std::cout << "Energy error: " << world.simulation.getEnergyError() << "%\n";
		window.clear();
		window.draw(world);
		window.setView(window.getDefaultView());
		window.draw(energyError);
		window.display();
	}

	return 0;
}
