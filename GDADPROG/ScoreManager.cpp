#include "ScoreManager.h"
#include <iostream>
ScoreManager * ScoreManager::sharedInstance = nullptr;

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
int ScoreManager::getScore()
{
	return this->score;
}
int ScoreManager::getDeaths()
{
	return this->deaths;

}
bool ScoreManager::getFlag()
{
	return this->isOver;
}
void ScoreManager::reset()
{
	this->score = 0;
	this->deaths = 0;
	this->isOver = false;
}
void ScoreManager::setDeath(int death)
{
	this->deaths = death;
}

void ScoreManager::setFlag(bool flag)
{
	this->isOver = flag;
}