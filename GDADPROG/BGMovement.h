#pragma once
#include "AbstractComponent.h"

class BGMovement : public AbstractComponent {
public:
	BGMovement(std::string name);
	void perform();

private:
	float SPEED_MULTIPLIER = 400.0f; //100.0f
};
