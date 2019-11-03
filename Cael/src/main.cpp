#include <SFML/Graphics.hpp>
#include "../World.h"
#include <iostream>
//world object should have dimension
int main()
{
	//Cael::Simulation simulation;
	World world;
	world.simulation.initialState.initFromFile("resources/solarsystem.txt");
	world.simulation.setIntegrator(Cael::EULER);
	world.simulation.setMethod(Cael::SQUARE);
	world.simulation.initialize();
	world.simulation.deltaTime = 20.0;
	world.scale = 1e-6;
	world.camera.followIndex = 1;
	//std::cin.get();
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			world.handleEvent(event, window);
		}
		world.update(window);
		world.simulation.step();
		window.clear();
		window.draw(world);
		window.display();
	}

	return 0;
}
