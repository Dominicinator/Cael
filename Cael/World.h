#pragma once
#include "Simulation.h"
#include <SFML/Graphics.hpp>

enum ParticleStyle { SOLID, TRANSPARENT};
class MousePan
{
public:
	Cael::vec2d mouseStart;
	Cael::vec2d cameraStart;


	MousePan();
	virtual ~MousePan();

	Cael::vec2d getDelta(Cael::vec2d position);
};
class Camera
{
public:
	sf::View view;
	MousePan pan;
	bool panning;
	Cael::SimulationState* stateptr;
	int followIndex = -1;

	void startPan(const Cael::vec2d & mousePosition);
	void endPan();
	void update(const Cael::vec2d & mousePosition, const float & scale);

	Camera();
	Camera(const float & x1, const float & y1, const float & x2, const float & y2);
	virtual ~Camera();
};
class World : public sf::Drawable
{
private:
	void doMousePress(const sf::Event & event, sf::RenderTarget & target);
	void doMouseRelease(const sf::Event & event, sf::RenderTarget & target);
	void doMouseScroll(const sf::Event & event, sf::RenderTarget & target);
	void doKeyBoardPress(const sf::Event & event, sf::RenderTarget & target);
public:
	Cael::Simulation simulation;
	Camera camera;
	double scale;

	World();
	virtual ~World();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void update(sf::RenderWindow & window);
	void handleEvent(const sf::Event & event, sf::RenderTarget & target);
	Cael::vec2d windowWorldTransform(const Cael::vec2d & pos, sf::RenderTarget & target);
	
};

class ParticleShape : public sf::Drawable
{
public:
	const Cael::Particle & particle;
	ParticleStyle style;

	double scale;

	ParticleShape(const Cael::Particle & p);
	ParticleShape(const Cael::Particle & p, const double & scl, const ParticleStyle & stl);
	virtual ~ParticleShape();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
};