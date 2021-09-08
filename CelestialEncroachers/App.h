#ifndef APP_HEADER
#define APP_HEADER

#include "SFML/Graphics.hpp"
#include "Player.h"

class App
{
public:
	App();
	~App();

	void Init();
	void Run();

private:
	sf::RenderWindow myWindow;
	sf::Clock myDeltaClock;
	float myDeltaTime;

	Player myPlayer;

	sf::Texture myPlayerTexture;
	sf::Texture* myBulletTexture;
	sf::Texture* myEnemy1Texture;
	sf::Texture* myEnemy2Texture;
	sf::Texture* myEnemy3Texture;
};


#endif