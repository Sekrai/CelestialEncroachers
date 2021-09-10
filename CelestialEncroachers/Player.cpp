#include "Player.h"
#include "BulletManager.h"

Player::Player()
	:mySprite(),
	mySpeed(0),
	myHealth(0),
	myScreenWidth(0),
	myAttackTimer(0),
	myAttackDelay(0),
	myHealth1Sprite(),
	myHealth2Sprite(),
	myHealth3Sprite(),
	myHasAttacked(false)
{
}

Player::~Player()
{
}

void Player::Init(sf::Texture& aTexture, sf::Vector2f aStartPos, int aScreenWidth, float aSpeed, float anAttackDelay, int someHealth)
{
	mySpeed = aSpeed;
	myHealth = someHealth;
	myAttackDelay = anAttackDelay;
	myScreenWidth = aScreenWidth - aTexture.getSize().x;

	mySprite.setTexture(aTexture);
	mySprite.setPosition(aStartPos);

	sf::Vector2f tempHealthPos(140, 10);
	myHealth1Sprite.setTexture(aTexture);
	myHealth1Sprite.setPosition(tempHealthPos);

	tempHealthPos.x += aTexture.getSize().x + 10;
	myHealth2Sprite.setTexture(aTexture);
	myHealth2Sprite.setPosition(tempHealthPos);

	tempHealthPos.x += aTexture.getSize().x + 10;
	myHealth3Sprite.setTexture(aTexture);
	myHealth3Sprite.setPosition(tempHealthPos);
}

bool Player::Update(float aDeltaTime)
{
	myAttackTimer += aDeltaTime;

	if (BulletManager::CheckCollision(mySprite.getGlobalBounds()) == true)
	{
		myHealth--;

		if (myHealth <= 0)
		{
			return false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (mySprite.getPosition().x > 0)													  //Put it as as seperate if to make sure it's not checking it when A is not held
		{
			mySprite.move(sf::Vector2f(-mySpeed * aDeltaTime, 0));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (mySprite.getPosition().x < myScreenWidth)													  //Put it as as seperate if to make sure it's not checking it when D is not held
		{
			mySprite.move(sf::Vector2f(mySpeed * aDeltaTime, 0));
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
	{
		if (myAttackTimer >= myAttackDelay)
		{
			myAttackTimer = 0;
			myHasAttacked = true;

			BulletManager::AddBullet(mySprite.getPosition() + sf::Vector2f(mySprite.getLocalBounds().width / 2, 0));
		}
	}

	return true;
}

void Player::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(mySprite);

	if (myHealth >= 1)
	{
		aWindow.draw(myHealth1Sprite);
	}
	if (myHealth >= 2)
	{
		aWindow.draw(myHealth2Sprite);
	}
	if (myHealth >= 3)
	{
		aWindow.draw(myHealth3Sprite);
	}
}

void Player::Reset()
{
	myHealth = 3;
	mySprite.setPosition(sf::Vector2f((myScreenWidth / 2) - (mySprite.getGlobalBounds().width / 2), mySprite.getPosition().y));
	myHasAttacked = false;
}

int Player::GetHealth()
{
	return myHealth;
}

void Player::SetHealth(const int& someHealth)
{
	myHealth = someHealth;
}

sf::Sprite& Player::GetSprite()
{
	return mySprite;
}

const sf::FloatRect& Player::GetCollisionBox()
{
	return mySprite.getGlobalBounds();
}

bool Player::GetHasAttacked()
{
	return myHasAttacked;
}
