#include "BulletManager.h"

CU::GrowingArray<Bullet> BulletManager::myBullets;
sf::Texture *BulletManager::myBulletTexture;

BulletManager::~BulletManager()
{
}

void BulletManager::Init(sf::Texture *aBulletTexture)
{
	myBullets.Init(10);
	myBulletTexture = aBulletTexture;
}

void BulletManager::Update(float aDeltaTime)
{
	for (int i = 0; i < myBullets.Count(); i++)
	{
		if (myBullets[i].Update(aDeltaTime) == false)
		{
			myBullets.RemoveAt(i);
			i--;
			continue;
		}
	}
}

void BulletManager::Draw(sf::RenderWindow& aWindow)
{
	for (int i = 0; i < myBullets.Count(); i++)
	{
		myBullets[i].Draw(aWindow);
	}
}

void BulletManager::AddBullet(Bullet& aBullet)
{
	myBullets.Add(aBullet);
}

void BulletManager::AddBullet(sf::Vector2f aStartPos, float aSpeed, sf::Vector2f aDirection, int anOutOfBounds)
{
	Bullet tempBullet;
	tempBullet.Init(*myBulletTexture, aStartPos, aSpeed, aDirection, anOutOfBounds);
	myBullets.Add(tempBullet);
}
