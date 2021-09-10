#ifndef SCORE_MANAGER_HEADER
#define SCORE_MANAGER_HEADER

#include "SFML/Graphics.hpp"
#include <sstream>

class ScoreManager
{
public:
	~ScoreManager();

	static void Init(sf::Vector2u someScreenBounds, sf::Font *aFont);
	static void AddScore(int someScore);
	static void Draw(sf::RenderWindow& aWindow);

	static void Reset();
private:
	ScoreManager() {};

	static sf::Vector2u myScreenBounds;
	static sf::Text myText;
	static sf::Font *myFont;
	static int myScore;
	static 	std::stringstream myStream;
};

#endif