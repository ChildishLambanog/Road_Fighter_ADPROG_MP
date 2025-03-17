#pragma once
#include "AbstractGameObject.h"
#include "ButtonListener.h"

class BarQuitButton : public AGameObject, public ButtonListener {
public:
	BarQuitButton(std::string name);
	void initialize();

	void onButtonClicked(UIButton* button);
	void onButtonReleased(UIButton* button);
private:
	bool quitButtonPressed;
};

