#include "Player.h"
#include "BulletManager.h"

Player::Player()
	:mySprite(),
	mySpeed(0),
	myHealth(0),
	myScreenWidth(0),
	myAttackTimer(0),
	myAttackDelay(0)
{
}

Player::~Player()
{
}

void Player::Init(sf::Texture &aTexture, sf::Vector2f aStartPos, int aScreenWidth, float aSpeed, float anAttackDelay, int someHealth)
{
	mySpeed = aSpeed;
	myHealth = someHealth;
	myAttackDelay = anAttackDelay;
	myScreenWidth = aScreenWidth - aTexture.getSize().x;
	
	mySprite.setTexture(aTexture);
	mySprite.setPosition(aStartPos);
}

void Player::Update(float aDeltaTime)
{
	myAttackTimer += aDeltaTime;

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

			BulletManager::AddBullet(mySprite.getPosition() + sf::Vector2f(mySprite.getLocalBounds().width / 2, 0));
		}
	}
}

void Player::Draw(sf::RenderWindow &aWindow)
{
	aWindow.draw(mySprite);
}

int Player::GetHealth()
{
	return myHealth;
}

void Player::SetHealth(const int &someHealth)
{
	myHealth = someHealth;
}

sf::Sprite& Player::GetSprite()
{
	return mySprite;
}
