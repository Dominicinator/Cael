#include <SFML/Graphics.hpp>
#include "../World.h"
#include <iostream>
//world object should have dimension
int main()
{
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
		world.update(window);
		world.simulation.step();
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
