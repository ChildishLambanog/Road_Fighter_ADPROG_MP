#pragma once
#include "AbstractGameObject.h"
#include "ButtonListener.h"

class TitleScreenExit : public AGameObject, public ButtonListener {
public: 
	TitleScreenExit(std::string name);
	void initialize();

	void onButtonClicked(UIButton* button);
	void onButtonReleased(UIButton* button);
	bool quitPressed;
};

