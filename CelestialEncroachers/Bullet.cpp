#include "Bullet.h"

Bullet::Bullet()
:mySpeed(0),
myDirection(),
mySprite(),
myOutOfBounds(0)

{
}

Bullet::~Bullet()
{
}

void Bullet::Init(sf::Texture& aTexture, sf::Vector2f aStartPos, float aSpeed, sf::Vector2f aDirection, int anOutOfBounds)
{
	mySpeed = aSpeed;
	myOutOfBounds = anOutOfBounds;
	myDirection = aDirection;

	mySprite.setTexture(aTexture);
	mySprite.setPosition(aStartPos);
	
}

bool Bullet::Update(float aDeltaTime)
{
	mySprite.move(myDirection * mySpeed * aDeltaTime);

	if (myDirection.y > 0)
	{
		if (mySprite.getPosition().y > myOutOfBounds)
		{
			return false;
		}
	}
	else if (myDirection.y < 0)
	{
		if (mySprite.getPosition().y < myOutOfBounds)
		{
			return false;
		}
	}

	return true;
}

void Bullet::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);
}

sf::FloatRect Bullet::GetCollisionBox()
{
	return mySprite.getGlobalBounds();
}