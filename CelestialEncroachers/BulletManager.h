#ifndef BULLET_MANAGER_HEADER
#define BULLET_MANAGER_HEADER

#include "GrowingArray.h"
#include "Bullet.h"

class BulletManager
{
public:
	~BulletManager();

	static void Init(sf::Texture *aBulletTexture);
	static void Update(float aDeltaTime);
	static void Draw(sf::RenderWindow& aWindow);

	static void AddBullet(Bullet &aBullet);
	static void AddBullet(sf::Vector2f aStartPos, float aSpeed = 350, sf::Vector2f aDirection = sf::Vector2f(0, -1), int anOutOfBounds = 0);

	static bool CheckCollision(const sf::FloatRect& aCollisionBox);
private:
	BulletManager() {};

	static sf::Texture *myBulletTexture;
	static CU::GrowingArray<Bullet> myBullets;
};

#endif
