#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Bullet.h"


class Player
{
public:
	Player();
	~Player();

	void Init(sf::Texture &aTexture, sf::Vector2f aStartPos, int aScreenWidth, float aSpeed, float anAttackDelay = 1.f, int someHealth = 3);
	void Update(float aDeltaTime);
	void Draw(sf::RenderWindow &aWindow);

	int GetHealth();
	void SetHealth(const int &someHealth);

	sf::Sprite &GetSprite();
private:
	int myScreenWidth;

	float mySpeed;
	int myHealth;
	float myAttackTimer;
	float myAttackDelay;

	sf::Sprite mySprite;
};

#endif
