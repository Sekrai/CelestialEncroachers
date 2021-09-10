#ifndef ENEMY_MANAGER_HEADER
#define ENEMY_MANAGER_HEADER

#include "GrowingArray.h"
#include "Enemy.h"

class EnemyManager
{
public:
	~EnemyManager();

	static void Init(sf::Vector2u someScreenBounds);
	static bool Update(float aDeltaTime);
	static void Draw(sf::RenderWindow& aWindow);

	static void AddEnemy(Enemy& anEnemy);
	static void AddEnemy(sf::Texture* anEnemyTexture, sf::Vector2f aStartPos, sf::Vector2f aMoveDistance, int someHealth = 1, int someScoreWorth = 1, float anAttackDelay = 1.5f, float aMoveDelay = 1.f,  float aDelayRecution = 0.05f, sf::Vector2f aDirection = sf::Vector2f(1, 0));

	static bool CheckCollision(const sf::FloatRect& aCollisionBox);
	static bool EmptyCheck();
	static void Clear();
private:
	EnemyManager() {};

	static sf::Vector2u myScreenBounds;
	static CU::GrowingArray<Enemy> myEnemies;
};

#endif
