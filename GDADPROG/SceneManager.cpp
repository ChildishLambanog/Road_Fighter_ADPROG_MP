#include "SceneManager.h"
#include <iostream>

std::string SceneManager::MAIN_MENU_SCENE_NAME = "MainMenuScene";
std::string SceneManager::GAME_SCENE_NAME = "GameScene";

SceneManager* SceneManager::sharedInstance = nullptr;

SceneManager* SceneManager::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new SceneManager();
	}

	return sharedInstance;
}

void SceneManager::registerScene(AbstractScene* scene)
{
	std::cout << scene->getSceneName() << " registered! \n";
	this->storedScenes[scene->getSceneName()] = scene;
}

void SceneManager::checkLoadScene()
{
	if (this->isLoading)
	{
		this->unloadScene();
		this->activeScene = this->storedScenes[this->toLoadSceneName];
		this->activeScene->onLoadResources();
		this->activeScene->onLoadObjects();
		this->isLoading = false;
	}
}

void SceneManager::loadScene(std::string name)
{
	this->isLoading = true;
	this->toLoadSceneName = name;
}

void SceneManager::unloadScene()
{
	if (this->activeScene != nullptr)
	{
		this->activeScene->onUnloadObjects();
		this->activeScene->onUnloadResources();
	}
}

bool SceneManager::isSceneLoaded(std::string name)
{
	return this->activeScene->getSceneName() == name;
}

std::string SceneManager::getActiveScene()
{
	return this->activeScene->getSceneName();
}