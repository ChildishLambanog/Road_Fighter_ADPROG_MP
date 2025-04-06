#pragma once
class ScoreManager
{
public:
	static ScoreManager* getInstance();
	
	void addScore();

	
	void addDeath();

	float getScore();
	int getDeaths();
	void reset();

private:
	ScoreManager() {};
	ScoreManager(ScoreManager const&) {};
	ScoreManager& operator=(ScoreManager const&) {};
	static ScoreManager* sharedInstance;
	float score = 0;
	int deaths = 0;

};

