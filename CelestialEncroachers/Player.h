#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Bullet.h"


class Player
{
public:
	Player();
	~Player();

	void Init(sf::Texture &aTexture, sf::Vector2f aStartPos, int aScreenWidth, float aSpeed, float anAttackDelay = 1.f, int someHealth = 3);
	bool Update(float aDeltaTime);
	void Draw(sf::RenderWindow &aWindow);

	void Reset();

	int GetHealth();
	void SetHealth(const int &someHealth);
	sf::Sprite &GetSprite();
	const sf::FloatRect& GetCollisionBox();
	bool GetHasAttacked();
private:
	int myScreenWidth;

	bool myHasAttacked;

	float mySpeed;
	int myHealth;
	float myAttackTimer;
	float myAttackDelay;

	sf::Sprite mySprite;
	sf::Sprite myHealth1Sprite;
	sf::Sprite myHealth2Sprite;
	sf::Sprite myHealth3Sprite;
};

#endif
