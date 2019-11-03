#include "World.h"
#include <iostream>
MousePan::MousePan()
{
}

MousePan::~MousePan()
{
}

Cael::vec2d MousePan::getDelta(Cael::vec2d position)
{
	return position - mouseStart;
}

Camera::Camera()
{
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	view.setCenter(0.f, 0.f);
}

Camera::Camera(const float & x1, const float & y1, const float & x2, const float & y2)
{
	view.setViewport(sf::FloatRect(x1, y1, x2, y2));
	view.setCenter(0.f, 0.f);
}

Camera::~Camera() {}

void Camera::startPan(const Cael::vec2d & mousePosition)
{
	
	panning = true;
	pan.mouseStart = mousePosition;
	pan.cameraStart = Cael::vec2d(view.getCenter().x, view.getCenter().y);
	
}

void Camera::endPan()
{
	panning = false;
}

void Camera::update(const Cael::vec2d & mousePosition, const float & scale)
{
	//std::cout << panning << std::endl;
	if (panning)
	{
		//std::cout << "wow!" << std::endl;
		Cael::vec2d position = pan.cameraStart - pan.getDelta(mousePosition);
		view.setCenter(position.x(), position.y());
	}
	if (followIndex > -1)
	{
		Cael::vec2d pos = stateptr->particles[followIndex].position * scale;
		view.setCenter(pos.x(), pos.y());
	}
}

void World::doMousePress(const sf::Event & event, sf::RenderTarget & target)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		Cael::vec2d mouse(event.mouseButton.x, event.mouseButton.y);
		Cael::vec2d worldPos = windowWorldTransform(mouse, target);
		Cael::Particle* clickedParticle = nullptr;// simulation.clickedParticle(worldPos);
		
		if (clickedParticle == nullptr)
		{
			camera.followIndex = -1;
			camera.startPan(mouse);
		}
		else
		{
			//camera.followParticle = clickedParticle;
		}
	}
}

void World::doMouseRelease(const sf::Event & event, sf::RenderTarget & target)
{
	camera.endPan();
}

void World::doMouseScroll(const sf::Event & event, sf::RenderTarget & target)
{
	const int & delta = event.mouseWheelScroll.delta;
	if (delta > 0)
	{
		scale *= 1.05f;
		camera.view.setCenter(camera.view.getCenter() * 1.05f);
	}
	else if (delta < 0) {
		scale *= 0.95f;
		camera.view.setCenter(camera.view.getCenter() * 0.95f);
	}
}

void World::doKeyBoardPress(const sf::Event & event, sf::RenderTarget & target)
{
	if (event.key.code == sf::Keyboard::Tab)
	{
		++camera.followIndex;
	}
	if (camera.followIndex > simulation.state.particles.size() - 1)
	{
		camera.followIndex = 0;
	}
}

World::World()
{
	camera.stateptr = &simulation.state;
}

World::~World()
{
}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(camera.view);
	for (unsigned int i = 0; i < simulation.state.particles.size(); ++i)
	{
		ParticleShape particle(simulation.state.particles[i], scale, SOLID);
		target.draw(particle);
	}
	//target.setView(target.getDefaultView());
}

void World::update(sf::RenderWindow & window)
{
	Cael::vec2d mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	camera.update(mousePosition, scale);
	//if (!(frametime < 1.0f))
	//frametime = clock.getElapsedTime().asSeconds();
	//clock.restart();
	//++n;
	//frametime = frametime * (n / (n + 1)) + pos / (n + 1);
	//simulation.deltaTime = deltaTime * 0.00006;
	//std::cout << frametime << std::endl;
	//simulation.deltaTime = deltaTime * frametime;
}

void World::handleEvent(const sf::Event & event, sf::RenderTarget & target)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			doMousePress(event, target);
			break;
		}	
		case sf::Event::MouseButtonReleased:
		{
			doMouseRelease(event, target);
			break;
		}
		case sf::Event::MouseWheelScrolled:
		{
			doMouseScroll(event, target);
			break;
		}
		case sf::Event::KeyPressed:
		{
			doKeyBoardPress(event, target);
			break;
		}
	}

}
Cael::vec2d World::windowWorldTransform(const Cael::vec2d & pos, sf::RenderTarget & target)
{
	Cael::vec2d windowSize(target.getSize().x, target.getSize().y);
	Cael::vec2d cameraPos(camera.view.getCenter().x, camera.view.getCenter().y);
	return (pos - windowSize / 2 + cameraPos) / scale;
	//return (vec2d(pos.x - window.getSize().x / 2, pos.y - window.getSize().y / 2) + vec2d(camera.view.getCenter().x, camera.view.getCenter().y)) * (1 / scale);
}

ParticleShape::ParticleShape(const Cael::Particle & p)
	: particle(p) {}

ParticleShape::ParticleShape(const Cael::Particle & p, const double & scl, const ParticleStyle & stl)
	: particle(p), scale(scl), style(stl) {}

ParticleShape::~ParticleShape() {}

void ParticleShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::CircleShape body(particle.radius*scale);
	body.setOrigin(particle.radius*scale, particle.radius*scale);
	body.setPosition(particle.position[0] * scale, particle.position[1] * scale);
	if (style == TRANSPARENT)
	{
		body.setFillColor(sf::Color::Transparent);
		body.setOutlineColor(sf::Color::Red);
		body.setOutlineThickness(1.0);
	}
	else
	{
		body.setFillColor(sf::Color::Red);
	}
	target.draw(body);
}


