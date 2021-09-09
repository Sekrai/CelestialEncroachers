#include "ScoreManager.h"
#include <iostream>


sf::Vector2u ScoreManager::myScreenBounds;
sf::Text ScoreManager::myText;
sf::Font *ScoreManager::myFont;
int ScoreManager::myScore;
std::stringstream ScoreManager::myStream;

ScoreManager::~ScoreManager()
{
	
}

void ScoreManager::Init(sf::Vector2u someScreenBounds, sf::Font *aFont)
{
	myScore = 0;
	myScreenBounds = someScreenBounds;

	myFont = aFont;

	myText.setFont(*myFont);
	myText.setCharacterSize(16);
	myText.setFillColor(sf::Color::Green);
	myText.setPosition(sf::Vector2f(24 , 10));


	myStream << "Score: " << myScore;

	myText.setString(myStream.str());
}

void ScoreManager::AddScore(int someScore)
{
	myScore += someScore;
	myStream.str("");
	myStream << "Score: " << myScore;
	myText.setString(myStream.str());
}

void ScoreManager::Draw(sf::RenderWindow& aWindow)
{
	aWindow.draw(myText);
}
