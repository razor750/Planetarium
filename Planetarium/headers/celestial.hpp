#pragma once

#include <SFML/Graphics.hpp>
#include "object.hpp"
#include "objecttype.hpp"

using namespace std;
using namespace sf;

class Celestial : public Object
{
	CircleShape sphere;

public:
	virtual ObjectType type();
	Celestial(Vector2f position, Vector2f velocity, float mass, float radius, string name);
	float getRadius();
	Vector2f getPosition();
	void actualize(float dt);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
