#include "Player.h"
#include "SFML/Window.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 1024), "Celestial Encroachers");
	sf::Clock deltaClock;
	sf::Time deltaTime;

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Gfx/player.png"))
	{
	}

	Player defender;
	defender.Init(playerTexture, sf::Vector2f((window.getSize().x / 2) - (playerTexture.getSize().x / 2), window.getSize().y - playerTexture.getSize().y * 2), 250.f);

	while (window.isOpen())
	{
		deltaTime = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		defender.Update(deltaTime.asSeconds());


		window.clear();
		
		defender.Draw(window);

		window.display();
	}

	return 0;
}