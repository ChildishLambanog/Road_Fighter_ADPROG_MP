#include "GameScene.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "BGObject.h"
#include "CarPlayer.h"
#include "EnemyCar.h"
#include "EnemySwarmHandler.h"
#include "EmptyGameObject.h"
#include "MainMenuScreen.h"
#include "FontManager.h"
#include "ApplicationManager.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "BarQuitButton.h"
#include "TitleScreenExit.h"
#include <iostream>
#include "PhysicsManager.h"


GameScene::GameScene() : AbstractScene("GameScene")
{
}

void GameScene::onLoadResources()
{
}

void GameScene::onLoadObjects()
{
	TextureManager::getInstance()->loadAll();
	FontManager::getInstance()->loadAll();

	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	CarPlayer* carObject = new CarPlayer("CarObject");
	GameObjectManager::getInstance()->addObject(carObject);

	srand(time(nullptr));
	EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
	EnemySwarmHandler* swarmHandler = new EnemySwarmHandler(7, "SwarmHandler", enemiesManager);
	enemiesManager->attachComponent(swarmHandler);
	GameObjectManager::getInstance()->addObject(enemiesManager);



	MainMenuScreen* mainMenu = new MainMenuScreen("MainMenuScreen");
	GameObjectManager::getInstance()->addObject(mainMenu);
	mainMenu->setEnabled(false);

	TitleScreenExit* titleExit = new TitleScreenExit("TitleScreenExit");
	GameObjectManager::getInstance()->addObject(titleExit);
	titleExit->setEnabled(false);

	BarQuitButton* quitButton = new BarQuitButton("BarQuitButton");
	GameObjectManager::getInstance()->addObject(quitButton);
}

void GameScene::onUnloadResources()
{
}