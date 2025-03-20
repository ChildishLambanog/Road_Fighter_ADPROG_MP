#pragma once
#include "AbstractGameObject.h"
#include "AbstractPoolable.h"

class EnemyCar : public AbstractPoolable {
public:
	EnemyCar(std::string name);
	~EnemyCar();
	void initialize();

	void onRelease();
	void onActivate();
	AbstractPoolable* clone();

private:
	sf::Sprite* sprite = new sf::Sprite();
	int counter = 0;

	const int SPAWN_RANGE = 300;
};