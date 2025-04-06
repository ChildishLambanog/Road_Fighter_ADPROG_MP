#include "ScoreManager.h"
#include <iostream>
ScoreManager* ScoreManager::sharedInstance = nullptr;

ScoreManager* ScoreManager::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new ScoreManager();
	}
	return sharedInstance;
}

void ScoreManager::addScore()
{
	this->score += 2;
	std::cout << "Score: " << this->score << std::endl;
}
void ScoreManager::addDeath()
{
	this->deaths++;
}
float ScoreManager::getScore()
{
	return this->score;
}
int ScoreManager::getDeaths()
{
	return this->deaths;

}

void ScoreManager::reset()
{
	this->score = 0;
	this->deaths = 0;
}