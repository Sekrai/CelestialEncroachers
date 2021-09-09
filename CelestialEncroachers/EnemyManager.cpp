#include "EnemyManager.h"
#include "ScoreManager.h"

sf::Vector2u EnemyManager::myScreenBounds;
CU::GrowingArray<Enemy> EnemyManager::myEnemies;


EnemyManager::~EnemyManager()
{

}

void EnemyManager::Init(sf::Vector2u someScreenBounds)
{
	myEnemies.Init(10);

	myScreenBounds = someScreenBounds;
}

void EnemyManager::Update(float aDeltaTime)
{
	for (int i = 0; i < myEnemies.Count(); i++)
	{
		if (myEnemies[i].Update(aDeltaTime) == false)
		{
			for (int j = 0; j < myEnemies.Count(); j++)
			{
				myEnemies[j].MoveDown();
			}

			//myEnemies[i].SpeedUp();														 //Speeds up when changing direction, based on original game
			break;
		}
	}
}

void EnemyManager::Draw(sf::RenderWindow& aWindow)
{
	for (int i = 0; i < myEnemies.Count(); i++)
	{
		myEnemies[i].Draw(aWindow);
	}
}

void EnemyManager::AddEnemy(Enemy& anEnemy)
{
	myEnemies.Add(anEnemy);
}

void EnemyManager::AddEnemy(sf::Texture* anEnemyTexture, sf::Vector2f aStartPos, sf::Vector2f aMoveDistance, int someHealth, int someScoreWorth, float anAttackDelay, float aMoveDelay, float aDelayRecution, sf::Vector2f aDirection)
{
	Enemy tempEnemy;

	tempEnemy.Init(*anEnemyTexture, aStartPos, aMoveDistance, myScreenBounds, anAttackDelay, aMoveDelay, aDelayRecution, aDirection, someHealth, someScoreWorth);
	myEnemies.Add(tempEnemy);
}

bool EnemyManager::CheckCollision(const sf::FloatRect& aCollisionBox)
{
	for (int i = 0; i < myEnemies.Count(); i++)
	{
		if (myEnemies[i].GetCollisionBox().intersects(aCollisionBox))
		{
			myEnemies[i].Damage();
			if (myEnemies[i].GetHealth() <= 0)
			{
				myEnemies[i].SpeedUp();
				ScoreManager::AddScore(myEnemies[i].GetScoreWorth());
				myEnemies.RemoveAt(i);
			}

			return true;
		}
	}
	return false;
}
