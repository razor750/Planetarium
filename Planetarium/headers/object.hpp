#pragma once

#include <SFML/Graphics.hpp>
#include "objecttype.hpp"

using namespace std;
using namespace sf;

class Object : public Drawable
{
protected:
	Vector2f velocity = Vector2f(0,0);
	Vector2f position;
	float mass = 1;
	string name;

public:
	virtual ObjectType type();
	virtual Vector2f getPosition() = 0;
	virtual void actualize(float dt) = 0;
	void updateVelocity(Vector2f force);
	void setVelocity(Vector2f vel);
	void setPosition(Vector2f pos);
	virtual void updatePosition(float dt);
	float getMass();
	Vector2f getVelocity();
	string getName();
	virtual ~Object();
};
