#pragma once
#include "AbstractGameObject.h"

class AbstractPoolable : public AGameObject {
public:
	AbstractPoolable(std::string name);
	virtual void initialize() = 0;

	virtual void onRelease() = 0;

	virtual void onActivate() = 0;

	virtual AbstractPoolable* clone() = 0;
};

