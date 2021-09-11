#include "Enemy.h"
#include <iostream>
#include <string>
#include "BulletManager.h"

float Enemy::myMoveDelay;

Enemy::Enemy()
:myMoveDistance(),
myDirection(),
mySprite(),
myMoveTimer(0),
myDelayReduction(0),
myScreenBounds(),
myHealth(),
myScoreWorth(),
myAttackTimer(0),
myAttackDelay(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(sf::Texture& aTexture, sf::Vector2f aStartPos, sf::Vector2f aMoveDistance, sf::Vector2u someScreenBounds, float anAttackDelay, float aMoveDelay, float aDelayReduction, sf::Vector2f aDirection, int someHealth, int someScoreWorth)
{
	myMoveDelay = aMoveDelay;
	myDelayReduction = aDelayReduction;
	myDirection = aDirection;
	myScreenBounds = someScreenBounds;
	myHealth = someHealth;
	myScoreWorth = someScoreWorth;
	myAttackDelay = anAttackDelay;

	mySprite.setTexture(aTexture);
	mySprite.setPosition(aStartPos);

	myMoveDistance = aMoveDistance;
}

bool Enemy::Update(float aDeltaTime)
{
	if (mySprite.getPosition().x >= myScreenBounds.x - mySprite.getTexture()->getSize().x || mySprite.getPosition().x <= 0)
	{
		return false;
	}

	myMoveTimer += aDeltaTime;
	myAttackTimer += aDeltaTime;

	if (myMoveTimer >= myMoveDelay)
	{
		myMoveTimer = 0;
		mySprite.move(myDirection * myMoveDistance.x);
	}

	if (myAttackTimer >= myAttackDelay)
	{
		myAttackTimer = 0;
		BulletManager::AddBullet(sf::Vector2f(mySprite.getPosition() + sf::Vector2f(mySprite.getLocalBounds().width / 2, mySprite.getLocalBounds().height)), 300.f, sf::Vector2f(0, 1), myScreenBounds.y);
	}
	

	return true;
}

void Enemy::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);
}

bool Enemy::MoveDown()
{
	myMoveTimer = 0;
	myDirection.x *= -1;
	mySprite.move(sf::Vector2f(myDirection.x * 15.f, mySprite.getTexture()->getSize().y / 2));

	if (mySprite.getPosition().y >= myScreenBounds.y - 133)
	{
		return false;
	}

	/*std::cout << "Enemy Pos: " << mySprite.getPosition().x << " " << mySprite.getPosition().y << "\n";*/
	return true;
}

const sf::FloatRect& Enemy::GetCollisionBox()
{
	return mySprite.getGlobalBounds();
}

void Enemy::Damage(int someDamage)
{
	myHealth -= someDamage;
}

int Enemy::GetHealth()
{
	return myHealth;
}

int Enemy::GetScoreWorth()
{
	return myScoreWorth;
}

void Enemy::SpeedUp()
{
	if (myMoveDelay > 0.15f)
	{
		myMoveDelay -= myDelayReduction;
	}

	if (myAttackDelay > 3.5f)
	{
		myAttackDelay -= myDelayReduction;
	}
}
