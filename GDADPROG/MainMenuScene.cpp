#include "MainMenuScene.h"
#include "MainMenuScreen.h"
#include "GameObjectManager.h"
#include "TitleMenuScreen.h"
#include <iostream>

MainMenuScene::MainMenuScene() : AbstractScene("MainMenuScene")
{
}

void MainMenuScene::onLoadResources()
{

}

void MainMenuScene::onLoadObjects()
{
	TitleMenuScreen* menuScreen = new TitleMenuScreen("TitleMenuScreen");
	this->registerObject(menuScreen);
}

void MainMenuScene::onUnloadResources()
{
}