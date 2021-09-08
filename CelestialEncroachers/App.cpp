#include "App.h"
#include "SFML/Window.hpp"
#include <iostream>
#include "BulletManager.h"
#include "EnemyManager.h"

App::App()
:myWindow(sf::VideoMode(1280, 1024), "Celestial Encroachers")
{
}

App::~App()
{
	SAFE_DELETE(myBulletTexture);
}

void App::Init()
{

	if (!myPlayerTexture.loadFromFile("Gfx/player.png"))
	{
		std::cout << "Could not load player \n";
	}

	myBulletTexture = new sf::Texture();
	if (!myBulletTexture->loadFromFile("Gfx/shot1.png"))
	{
		std::cout << "Could not load bullet \n";
	}

	myEnemy1Texture = new sf::Texture();
	if (!myEnemy1Texture->loadFromFile("Gfx/enemy1.png"))
	{
		std::cout << "Could not load bullet \n";
	}

	BulletManager::Init(myBulletTexture);
	EnemyManager::Init(myEnemy1Texture, myWindow.getSize());
	
	myPlayer.Init(myPlayerTexture, sf::Vector2f((myWindow.getSize().x / 2) - (myPlayerTexture.getSize().x / 2), myWindow.getSize().y - (myPlayerTexture.getSize().y * 3)), myWindow.getSize().x, 250.f);

	sf::Vector2f tempEnemyStartPos(myEnemy1Texture->getSize().x, myEnemy1Texture->getSize().y);
	float tempOffset = myBulletTexture->getSize().x * 2;

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			EnemyManager::AddEnemy(tempEnemyStartPos);
			tempEnemyStartPos.y += myEnemy1Texture->getSize().y + tempOffset;
		}
		tempEnemyStartPos.x += myEnemy1Texture->getSize().x + tempOffset;
		tempEnemyStartPos.y = myEnemy1Texture->getSize().y;
	}
}

void App::Run()
{
	while (myWindow.isOpen())
	{
		myDeltaTime = myDeltaClock.restart().asSeconds();
		sf::Event event;
		while (myWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				myWindow.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			myWindow.close();
		}


		myPlayer.Update(myDeltaTime);
		BulletManager::Update(myDeltaTime);
		EnemyManager::Update(myDeltaTime);

		myWindow.clear();

		BulletManager::Draw(myWindow);
		EnemyManager::Draw(myWindow);
		myPlayer.Draw(myWindow);

		myWindow.display();
	}
}
