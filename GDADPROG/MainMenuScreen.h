#pragma once
#include "AbstractGameObject.h"
#include <string>
#include "ButtonListener.h"

class MainMenuScreen : public AGameObject, public ButtonListener {
public:
	MainMenuScreen(std::string name);

	void initialize();

	void onButtonClicked(UIButton* button);
	void onButtonReleased(UIButton* button);
};