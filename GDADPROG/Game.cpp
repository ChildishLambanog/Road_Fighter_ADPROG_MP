#include "Game.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "SceneManager.h"
#include <iostream>

Game::Game() : mWindow(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "Rameses Amar & Ira Villanueva"), mSampleEntity()
{

}

void Game::addEntity(std::string key, float x, float y)
{
	sf::Texture* texture = TextureManager::getInstance()->getTexture(key);
	Entity* newEntity = Entity::createEntity(texture, x, y);
	mEntityList.push_back(newEntity);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time elapsedTime = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		processEvents();
		deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;
		elapsedTime += deltaTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
		SceneManager::getInstance()->checkLoadScene();
	}
}

void Game::render()
{
	mWindow.clear();
	GameObjectManager::getInstance()->draw(&mWindow);
	mWindow.display();
}

void Game::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
		GameObjectManager::getInstance()->processInput(event);
	}
}

void Game::update(sf::Time deltaTime)
{
	if (!ApplicationManager::getInstance()->isPaused())
	{
		GameObjectManager::getInstance()->update(deltaTime);
	}
}