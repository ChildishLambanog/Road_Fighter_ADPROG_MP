#pragma once
#include "AbstractScene.h"
class GameScene : public AbstractScene {
public:
	GameScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};
