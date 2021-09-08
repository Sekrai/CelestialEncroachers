#include "EnemyManager.h"

sf::Vector2u EnemyManager::myScroundBounds;
CU::GrowingArray<Enemy> EnemyManager::myEnemies;
sf::Texture* EnemyManager::myEnemyTexture;

EnemyManager::~EnemyManager()
{
	SAFE_DELETE(myEnemyTexture);
}

void EnemyManager::Init(sf::Texture* anEnemyTexture, sf::Vector2u someScroundBounds)
{
	myEnemies.Init(10);
	myEnemyTexture = anEnemyTexture;
	myScroundBounds = someScroundBounds;
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

void EnemyManager::AddEnemy(sf::Vector2f aStartPos, float aMoveDelay, float aDelayRecution, sf::Vector2f aDirection)
{
	Enemy tempEnemy;
	tempEnemy.Init(*myEnemyTexture, aStartPos, myScroundBounds, aMoveDelay, aDelayRecution, aDirection);
	myEnemies.Add(tempEnemy);
}
