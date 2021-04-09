#include "celestial.hpp"

ObjectType Celestial::type()
{
	return CELESTIAL;
}

Celestial::Celestial(Vector2f position, Vector2f velocity, float mass, float radius, string name)
{
	this->position = position;
	this->velocity = velocity;
	this->mass = mass;
	this->name = name;

	sphere.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255));
	sphere.setRadius(radius);
	sphere.setOrigin(radius, radius);
}

float Celestial::getRadius()
{
	return sphere.getRadius();
}

Vector2f Celestial::getPosition()
{
	return position;
}

void Celestial::actualize(float dt)
{
	sphere.setPosition(position.x, 1080-position.y);
}

void Celestial::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sphere, states);
}
