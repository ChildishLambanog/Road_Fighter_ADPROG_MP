#pragma once
#include "AbstractGameObject.h"

class CarPlayer : public AGameObject {
public:
	CarPlayer(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

};

