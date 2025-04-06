#pragma once
class ScoreManager
{
public:
	static ScoreManager* getInstance();

	void addScore();


	void addDeath();
	void setFlag(bool flag);

	int getScore();
	int getDeaths();
	void setDeath(int death);
	void reset();
	bool getFlag();
private:
	ScoreManager() {};
	ScoreManager(ScoreManager const&) {};
	ScoreManager& operator=(ScoreManager const&) {};
	static ScoreManager* sharedInstance;
	int score = 0;
	int deaths = 0;
	bool isOver = false;

};
;

