#pragma once
#include "AbstractGameObject.h"

class EmptyGameObject : public AGameObject {
public: 
	EmptyGameObject(std::string name);
	void initialize();

};