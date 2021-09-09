#include "Enemy.h"
#include <iostream>
#include <string>

Enemy::Enemy()
:myMoveDistance(),
myDirection(),
mySprite(),
myMoveTimer(0),
myMoveDelay(0),
myDelayReduction(0),
myScroundBounds()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(sf::Texture& aTexture, sf::Vector2f aStartPos, sf::Vector2u someScreenBounds, float aMoveDelay, float aDelayReduction, sf::Vector2f aDirection, int someHealth)
{
	myMoveDelay = aMoveDelay;
	myDelayReduction = aDelayReduction;
	myDirection = aDirection;
	myScroundBounds = someScreenBounds;
	myHealth = someHealth;

	mySprite.setTexture(aTexture);
	mySprite.setPosition(aStartPos);

	myMoveDistance = sf::Vector2f(aTexture.getSize().x / 4, aTexture.getSize().y / 2);
}

bool Enemy::Update(float aDeltaTime)
{
	if (mySprite.getPosition().x >= myScroundBounds.x - mySprite.getTexture()->getSize().x || mySprite.getPosition().x <= 0)
	{
		return false;
	}

	myMoveTimer += aDeltaTime;

	if (myMoveTimer >= myMoveDelay)
	{
		myMoveTimer = 0;
		mySprite.move(myDirection * myMoveDistance.x);
	}
	

	return true;
}

void Enemy::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);
}

void Enemy::MoveDown()
{
	myDirection.x *= -1;
	mySprite.move(sf::Vector2f(myDirection.x * 10.f, mySprite.getTexture()->getSize().y / 2));

	if (myMoveDelay > 0.15f)
	{
		myMoveDelay -= myDelayReduction;
	}

	/*std::cout << "Enemy Pos: " << mySprite.getPosition().x << " " << mySprite.getPosition().y << "\n";*/
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
