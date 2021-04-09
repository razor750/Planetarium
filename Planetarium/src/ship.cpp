#include "ship.hpp"

ObjectType Ship::type()
{
	return SHIP;
}

Ship::Ship(Vector2f position, Vector2f velocity, float mass, float radius, string name)
{
	this->position = position;
	this->velocity = velocity;
	this->mass = mass;
	this->name = name;
	momentOfInertia = mass * radius;

	body.setRadius(radius);
	body.setPointCount(3);
	body.setFillColor(Color::White);
	body.setOrigin(radius, radius);

	drive.setSize(Vector2f(radius, radius/2));
	drive.setFillColor(Color(100,100,100));
	drive.setOrigin(Vector2f(radius/2,-radius/2));
}

Vector2f Ship::getPosition()
{
	return position;
}

void Ship::actualize(float dt)
{
	body.setRotation(body.getRotation()+dt*rotationRate);
	body.setPosition(position.x, 1080-position.y);
	drive.setRotation(body.getRotation());
	drive.setPosition(position.x, 1080-position.y);
}

void Ship::accelerateRotary(float rate)
{
	rotationRate += rate;
}

void Ship::accelerateLinear(float rate)
{
	velocity.x += sin(body.getRotation() * M_PI/180.f) * rate;
	velocity.y += cos(body.getRotation() * M_PI/180.f) * rate;
	drive.setFillColor(Color::Red);
}

void Ship::resetColor()
{
	drive.setFillColor(Color(100,100,100));
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(drive, states);
	target.draw(body, states);
}
