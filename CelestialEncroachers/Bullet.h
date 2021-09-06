#ifndef BULLET_HEADER
#define BULLET_HEADER

#include "SFML/Graphics.hpp"

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init(sf::Texture& aTexture, sf::Vector2f aStartPos, float aSpeed, sf::Vector2f aDirection = sf::Vector2f(0, -1), int anOutOfBounds = 0);
	bool Update(float aDeltaTime);
	void Draw(sf::RenderWindow& aWindow);

private:
	int myOutOfBounds;

	float mySpeed;
	sf::Vector2f myDirection;

	sf::Sprite mySprite;
};


#endif