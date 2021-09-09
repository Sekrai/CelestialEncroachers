#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include "SFML/Graphics.hpp"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init(sf::Texture& aTexture, sf::Vector2f aStartPos,  sf::Vector2u someScreenBounds, float aMoveDelay = 1.f, float aDelayReduction = 0.1f, sf::Vector2f aDirection = sf::Vector2f(1, 0), int someHealth = 1);
	bool Update(float aDeltaTime);
	void Draw(sf::RenderWindow& aWindow);

	void MoveDown();

	const sf::FloatRect& GetCollisionBox();

	void Damage(int someDamage = 1);
	int GetHealth();
private:
	sf::Vector2u myScroundBounds;


	float myMoveTimer;
	float myMoveDelay;
	float myDelayReduction;
	sf::Vector2f myMoveDistance;
	sf::Vector2f myDirection;

	sf::Sprite mySprite;

	int myHealth;
};


#endif