#pragma once
#include "AbstractGameObject.h"
#include "ButtonListener.h"

class GameOverScreen : public AGameObject, public ButtonListener {
public:
	GameOverScreen(std::string name);
	void initialize();

	void onButtonClicked(UIButton* button);
	void onButtonReleased(UIButton* button);
	bool quitPressed;

	
};


