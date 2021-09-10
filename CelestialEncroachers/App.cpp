#include "App.h"
#include "SFML/Window.hpp"
#include <iostream>
#include "BulletManager.h"
#include "EnemyManager.h"
#include "ScoreManager.h"

App::App()
:myWindow(),
myBackgroundTexture(),
myBackground(),
myBulletTexture(),
myPlayer(),
myPlayerTexture(),
myDeltaClock(),
myDeltaTime(),
myEnemy1Texture(),
myEnemy2Texture(),
myEnemy3Texture(),
myFont(),
myGameOverFlag(false),
myGameOverText(),
myEnemyMinAttackDelay(5.f),
myEnemySpeedBonus(1.f),
myEnemyScoreMod(0)
{
}

App::~App()
{
	SAFE_DELETE(myBulletTexture);
	SAFE_DELETE(myBackgroundTexture);
	SAFE_DELETE(myEnemy1Texture);
	SAFE_DELETE(myEnemy2Texture);
	SAFE_DELETE(myEnemy3Texture);
	SAFE_DELETE(myFont);
	
}

void App::Init()
{
	myBackgroundTexture = new sf::Texture();
	if (!myBackgroundTexture->loadFromFile("Gfx/background.png"))
	{
		std::cout << "Could not load background \n";
	}

	myBackground.setTexture(*myBackgroundTexture);
	myBackground.setPosition(sf::Vector2f(0, 0));

	myWindow.create(sf::VideoMode(myBackgroundTexture->getSize().x, myBackgroundTexture->getSize().y), "Celestial Encroachers");

	srand(time(NULL));

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
		std::cout << "Could not load Enemy \n";
	}

	myEnemy2Texture = new sf::Texture();
	if (!myEnemy2Texture->loadFromFile("Gfx/enemy2.png"))
	{
		std::cout << "Could not load Enemy2 \n";
	}

	myEnemy3Texture = new sf::Texture();
	if (!myEnemy3Texture->loadFromFile("Gfx/enemy3.png"))
	{
		std::cout << "Could not load Enemy3 \n";
	}

	myFont = new sf::Font();
	if (!myFont->loadFromFile("Gfx/BitBold.ttf"))
	{
		std::cout << "Could not load font\n";
	}

	BulletManager::Init(myBulletTexture);
	EnemyManager::Init( myWindow.getSize());
	ScoreManager::Init(myWindow.getSize(), myFont);
	
	myPlayer.Init(myPlayerTexture, sf::Vector2f((myWindow.getSize().x / 2) - (myPlayerTexture.getSize().x / 2), myWindow.getSize().y - (myPlayerTexture.getSize().y * 3)), myWindow.getSize().x, 250.f);


	myGameOverText.setFont(*myFont);
	myGameOverText.setCharacterSize(86);
	myGameOverText.setFillColor(sf::Color::Green);
	myGameOverText.setPosition(sf::Vector2f(myWindow.getSize().x / 4, (myWindow.getSize().y / 2) - 100));
	myGameOverText.setString("GAME OVER");

	SpawnEnemies();
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

		if (EnemyManager::EmptyCheck() == true)
		{
			myEnemyMinAttackDelay -= 0.1f;
			myEnemySpeedBonus += 0.1f;
			myEnemyScoreMod++;

			SpawnEnemies();
		}

		BulletManager::Update(myDeltaTime);

		if (EnemyManager::Update(myDeltaTime) == false)
		{
			GameOver();
		}

		if (myPlayer.Update(myDeltaTime) == false)
		{
			GameOver();
		}

		myWindow.clear();
		myWindow.draw(myBackground);

		BulletManager::Draw(myWindow);
		EnemyManager::Draw(myWindow);
		ScoreManager::Draw(myWindow);
		myPlayer.Draw(myWindow);

		if (myGameOverFlag == true)
		{
			myWindow.draw(myGameOverText);
		}

		myWindow.display();
	}
}

void App::SpawnEnemies()
{
	sf::Vector2f tempMoveDistance(myEnemy1Texture->getSize().x / 4, myEnemy1Texture->getSize().y / 2);
	tempMoveDistance *= myEnemySpeedBonus;

	sf::Vector2f tempEnemyStartPos(myEnemy1Texture->getSize().x, myEnemy1Texture->getSize().y + 33);
	float tempOffset = myBulletTexture->getSize().x * 2;

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			if (y < 2)
			{
				EnemyManager::AddEnemy(myEnemy3Texture, tempEnemyStartPos, tempMoveDistance, 3, 3 + myEnemyScoreMod, myEnemyMinAttackDelay + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/ 7.5f)));
			}
			else if (y < 4)
			{
				EnemyManager::AddEnemy(myEnemy2Texture, tempEnemyStartPos, tempMoveDistance, 2, 2 + myEnemyScoreMod, myEnemyMinAttackDelay + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 10.f)));
			}
			else
			{
				EnemyManager::AddEnemy(myEnemy1Texture, tempEnemyStartPos, tempMoveDistance, 1, 1 + myEnemyScoreMod, myEnemyMinAttackDelay + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 15.f)));
			}
			tempEnemyStartPos.y += myEnemy1Texture->getSize().y + tempOffset;
		}
		tempEnemyStartPos.x += myEnemy1Texture->getSize().x + tempOffset;
		tempEnemyStartPos.y = myEnemy1Texture->getSize().y + 33;
	}
}

void App::GameOver()
{
	myGameOverFlag = true;

	//TODO Add code for restarting
}
