#pragma once
#include "AbstractGameObject.h"
#include "ButtonListener.h"

class TitleMenuScreen : public AGameObject, public ButtonListener {
public:
	TitleMenuScreen(std::string name);

	void initialize();

	void onButtonClicked(UIButton* button);
	void onButtonReleased(UIButton* button);
	bool quitPressed;
};

