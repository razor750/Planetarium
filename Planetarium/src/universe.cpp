#include "universe.hpp"

Universe::Universe()
{
	objects.push_back(new Celestial(Vector2f(1920/2, 1080/2), Vector2f(0,0), 1.6e13, 40, "sun"));
	objects.push_back(new Celestial(Vector2f(1920/2 + 400, 1080/2), Vector2f(0,20), 1e11, 10, "planet-a"));
	objects.push_back(new Celestial(Vector2f(1920/2 - 400, 1080/2), Vector2f(0,-20), 1e11, 10, "planet-b"));
	objects.push_back(new Celestial(Vector2f(1920/2, 1080/2 + 400), Vector2f(-20,0), 1e11, 10, "planet-c"));
	objects.push_back(new Celestial(Vector2f(1920/2, 1080/2 - 400), Vector2f(20,0), 1e11, 10, "planet-d"));
	objects.push_back(new Celestial(Vector2f(1920/2, 1080/2 - 500), Vector2f(15,0), 1e11, 10, "planet-e"));
	objects.push_back(player = new Ship(Vector2f(1920/2 - 500, 1080/2 - 500), Vector2f(0,0), 1e10, 10, "player"));

//	RANDOM CELESTIALS GENERATION
//	for(int i=0; i<100; i++)
//	{
//		float r = rand()%7+1;
//		float mass = 1e10*r*r;
//		objects.push_back(new Celestial(Vector2f(rand() % 1920, rand() % 1080), Vector2f((rand() % 20) - 10, (rand() % 20) - 10), mass, r, "planet-a"));
//	}
}

void Universe::operator() ()
{
	float dt = clk.restart().asSeconds();
	handleInput();
	list<pair<Object*, Object*>> collisions;
	for(auto o1:objects)
	{
		float mass = o1->getMass();
		Vector2f position = o1->getPosition();
		Vector2f force(0,0);
		for(auto o2:objects)
			if(o1 != o2)
			{
				double r = hypot(position.x-o2->getPosition().x, position.y-o2->getPosition().y);
				float f = (6.67*1e-11) * (mass*o2->getMass()) / (r*r);
				force.x += f * sin( atan2( o2->getPosition().x - position.x, o2->getPosition().y - position.y ) );
				force.y += f * cos( atan2( o2->getPosition().x - position.x, o2->getPosition().y - position.y ) );

				bool check = true;
				for(auto c:collisions)
					if(c.first == o2 && c.second == o1)
						check = false;
				if(check)
					if(o1->type() == CELESTIAL && o2->type() == CELESTIAL)
					{
						Celestial& c1 = dynamic_cast<Celestial&>(*o1);
						Celestial& c2 = dynamic_cast<Celestial&>(*o2);
						if(c1.getRadius() + c2.getRadius() > r)
						{
							repairOverlap(c1, c2);
							collision(c1, c2);
							collisions.push_back(pair<Object*, Object*>(o1,o2));
						}
					}
			}
		o1->updateVelocity(force);
	}
	for(auto o:objects)
	{
		o->updatePosition(dt);
		o->actualize(dt);
	}
}

void Universe::repairOverlap(Celestial & c1, Celestial & c2)
{
	Vector2f x1 = c1.getPosition();
	Vector2f x2 = c2.getPosition();
	float r1 = c1.getRadius();
	float r2 = c2.getRadius();

	float overlap = r1 + r2 - hypot(x1.x-x2.x, x1.y-x2.y);
	float angle = atan2(x2.x-x1.x, x2.y-x1.y);

	x1.x += (r1/(r1+r2))*overlap * -sin(angle);
	x1.y += (r1/(r1+r2))*overlap * -cos(angle);

	x2.x -= (r2/(r1+r2))*overlap * -sin(angle);
	x2.y -= (r2/(r1+r2))*overlap * -cos(angle);

	c1.setPosition(x1);
	c2.setPosition(x2);
}

void Universe::collision(Celestial & c1, Celestial & c2)
{
	Vector2f v1 = c1.getVelocity();
	Vector2f v2 = c2.getVelocity();
	Vector2f v1p, v2p;
	v1p = (v1 * (c1.getMass()-c2.getMass()) + 2*c2.getMass()*v2) / (c1.getMass() + c2.getMass());
	v2p = (v2 * (c2.getMass()-c1.getMass()) + 2*c1.getMass()*v1) / (c2.getMass() + c1.getMass());
	c1.setVelocity(v1p);
	c2.setVelocity(v2p);
}

float Universe::dotProduct(Vector2f v1, Vector2f v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}
void Universe::handleInput()
{
	if(Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::Up))
		player->accelerateLinear(1);
	else player->resetColor();
	if(Keyboard::isKeyPressed(Keyboard::Left))
		player->accelerateRotary(-1);
	if(Keyboard::isKeyPressed(Keyboard::Right))
		player->accelerateRotary(1);
}

Universe::~Universe()
{
	for(auto o:objects)
		delete o;
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto o:objects)
		target.draw(*o, states);
}
