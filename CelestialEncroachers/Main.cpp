#include "Player.h"
#include "SFML/Window.hpp"
#include <iostream>
#include "BulletManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 1024), "Celestial Encroachers");
	sf::Clock deltaClock;
	sf::Time deltaTime;

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Gfx/player.png"))
	{
		std::cout << "Could not load player \n";
	}

	sf::Texture* bulletTexture = new sf::Texture();
	if (!bulletTexture->loadFromFile("Gfx/shot1.png"))
	{
		std::cout << "Could not load bullet \n";
	}

	BulletManager::Init(bulletTexture);

	Player defender;
	defender.Init(playerTexture, sf::Vector2f((window.getSize().x / 2) - (playerTexture.getSize().x / 2), window.getSize().y - (playerTexture.getSize().y * 3)), window.getSize().x, 250.f);

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
		BulletManager::Update(deltaTime.asSeconds());

		window.clear();

		BulletManager::Draw(window);
		defender.Draw(window);

		window.display();
	}

	return 0;
}