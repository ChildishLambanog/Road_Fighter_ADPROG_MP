#pragma once
#include "AbstractComponent.h"

class EnemyBehaviour : public AbstractComponent {
public:
	enum EnemyMovementType { Delay = 0, Forward = 1, SlowForward = 2, Side = 3 };

	EnemyBehaviour(std::string name);
	void perform();
	void configure(float delay);
	void reset();

private:
	void isItOutOfBounds();
	const float SPEED_MULTIPLIER = 500.0f; //100.0f
	EnemyBehaviour::EnemyMovementType movementType = Forward;
	float tick = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
};	
