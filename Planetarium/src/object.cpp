#include "object.hpp"

ObjectType Object::type()
{
	return OBJECT;
}

void Object::updateVelocity(Vector2f force)
{
	velocity.x += force.x/mass;
	velocity.y += force.y/mass;
}

void Object::setVelocity(Vector2f vel)
{
	velocity = vel;
}

void Object::setPosition(Vector2f pos)
{
	position = pos;
}

void Object::updatePosition(float dt)
{
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
	if(position.x > 1920)
	{
		position.x = 1920;
		velocity.x *= -1;
	}
	if(position.x < 0)
	{
		position.x = 0;
		velocity.x *= -1;
	}
	if(position.y > 1080)
	{
		position.y = 1080;
		velocity.y *= -1;
	}
	if(position.y < 0)
	{
		position.y = 0;
		velocity.y *= -1;
	}
}

float Object::getMass()
	{
		return mass;
	}

Vector2f Object::getVelocity()
{
	return velocity;
}

string Object::getName()
{
	return name;
}

Object::~Object()
{

}
