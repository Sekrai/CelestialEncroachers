#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "SFML/Graphics.hpp"

class Player
{
public:
	Player();
	~Player();

	void Init(sf::Texture aTexture, sf::Vector2f aStartPos, float aSpeed, int someHealth = 3);
	void Update(float aDeltaTime);
	void Draw(sf::RenderWindow &aWindow);

	int GetHealth();
	void SetHealth(const int &someHealth);

	sf::Sprite &GetSprite();
private:
	float mySpeed;
	int myHealth;

	sf::Sprite mySprite;
};

#endif
