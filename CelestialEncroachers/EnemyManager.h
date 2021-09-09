#ifndef ENEMY_MANAGER_HEADER
#define ENEMY_MANAGER_HEADER

#include "GrowingArray.h"
#include "Enemy.h"

class EnemyManager
{
public:
	~EnemyManager();

	static void Init(sf::Texture* anEnemyTexture, sf::Vector2u someScroundBounds);
	static void Update(float aDeltaTime);
	static void Draw(sf::RenderWindow& aWindow);

	static void AddEnemy(Enemy& anEnemy);
	static void AddEnemy(sf::Vector2f aStartPos, float aMoveDelay = 1.f, float aDelayRecution = 0.1f, sf::Vector2f aDirection = sf::Vector2f(1, 0));

	static bool CheckCollision(const sf::FloatRect& aCollisionBox);
private:
	EnemyManager() {};

	static sf::Vector2u myScroundBounds;
	static sf::Texture* myEnemyTexture;
	static CU::GrowingArray<Enemy> myEnemies;
};

#endif
