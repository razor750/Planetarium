#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "universe.hpp"

using namespace sf;

int main() {
	RenderWindow window(sf::VideoMode::getDesktopMode(), "Planetarium", sf::Style::Fullscreen);
	Universe universe;

	srand(time(NULL));

	while(window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}
		universe();
		window.clear();
		window.draw(universe);
		window.display();
	}
}
