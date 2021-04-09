#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <cmath>
#include "object.hpp"
#include "celestial.hpp"
#include "ship.hpp"
#include "objecttype.hpp"

using namespace std;
using namespace sf;

class Universe : public Drawable
{
	list<Object*> objects;
	Clock clk;
	Ship* player;

public:
	Universe();
	void operator() ();
	void repairOverlap(Celestial & c1, Celestial & c2);
	void collision(Celestial & c1, Celestial & c2);
	float dotProduct(Vector2f v1, Vector2f v2);
	void handleInput();
	~Universe();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
