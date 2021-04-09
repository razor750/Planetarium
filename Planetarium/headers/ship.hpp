#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "object.hpp"
#include "objecttype.hpp"

using namespace std;
using namespace sf;

class Ship : public Object
{
	CircleShape body;
	RectangleShape drive;
	float momentOfInertia;
	float rotationRate=0;

public:
	virtual ObjectType type();
	Ship(Vector2f position, Vector2f velocity, float mass, float radius, string name);
	Vector2f getPosition();
	void actualize(float dt);
	void accelerateRotary(float rate);
	void accelerateLinear(float rate);
	void resetColor();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
