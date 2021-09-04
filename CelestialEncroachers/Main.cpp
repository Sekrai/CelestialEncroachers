#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 1024), "Celestial Encroachers");
	sf::CircleShape tempCircle(50);
	tempCircle.setFillColor(sf::Color::Green);

	float tempSpeed = 2.f;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
		{
			tempCircle.move(sf::Vector2f(-tempSpeed, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true)
		{
			tempCircle.move(sf::Vector2f(tempSpeed, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
		{
			tempCircle.move(sf::Vector2f(0, -tempSpeed));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
		{
			tempCircle.move(sf::Vector2f(0, tempSpeed));
		}



		window.clear();
		window.draw(tempCircle);
		window.display();
	}

	return 0;
}