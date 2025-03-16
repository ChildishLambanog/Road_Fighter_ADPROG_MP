#pragma once
#include "AbstractComponent.h"

class PlayerMovement : public AbstractComponent {
public:
	PlayerMovement(std::string name);
	void perform();
private:
	const float SPEED_MULTIPLIER = 300.0f;
};

