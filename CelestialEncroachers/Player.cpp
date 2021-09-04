#include "Player.h"

Player::Player()
	:mySprite(),
	mySpeed(0),
	myHealth(0)
{
}

Player::~Player()
{
}

void Player::Init(sf::Texture aTexture, sf::Vector2f aStartPos, float aSpeed, int someHealth)
{
	mySpeed = aSpeed;
	myHealth = someHealth;

	
	mySprite.setTexture(aTexture);
	mySprite.setPosition(aStartPos);
}

void Player::Update(float aDeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
	{
		mySprite.move(sf::Vector2f(-mySpeed * aDeltaTime, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true)
	{
		mySprite.move(sf::Vector2f(mySpeed * aDeltaTime, 0));
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
