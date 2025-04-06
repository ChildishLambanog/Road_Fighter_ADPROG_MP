#include "Game.h"
#include "TextureManager.h"
#include "SFXManager.h"
#include "GameObjectManager.h"
#include "BGObject.h"
#include "CarPlayer.h"
#include "EnemyCar.h"
#include "EmptyGameObject.h"
#include "EnemySwarmHandler.h"
#include "MainMenuScreen.h"
#include "FontManager.h"
#include "ApplicationManager.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "BarQuitButton.h"
#include "TitleMenuScreen.h"
#include "GameScene.h"
#include <SFML/Graphics.hpp>
#include "SFXManager.h"
#include <iostream>


Game::Game() : mWindow(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "Rameses Amar & Ira Villanueva"), mSampleEntity()
{
	ApplicationManager::getInstance()->initialize(&mWindow);
	TextureManager::getInstance()->loadAll();
	FontManager::getInstance()->loadAll();
	SceneManager::getInstance()->registerScene(new GameScene());

	SFXManager::getInstance()->loadAll();

	TitleMenuScreen* titleMenu = new TitleMenuScreen("TitleMenuScreen");
	GameObjectManager::getInstance()->addObject(titleMenu);
}

void Game::addEntity(std::string key, float x, float y)
{
	sf::Texture* texture = TextureManager::getInstance()->getTexture(key);
	Entity* newEntity = Entity::createEntity(texture, x, y);
	mEntityList.push_back(newEntity);
}

void Game::addSFX(std::string key)
{
	sf::SoundBuffer* soundEffects = SFXManager::getInstance()->getSound(key);

	
	if (key == "boom")
	{
		mSFXMapList[0] = soundEffects;

	}
	else if (key == "score")
	{
		mSFXMapList[1] = soundEffects;
	}
	else if (key == "SFX_3")
	{
		mSFXMapList[2] = soundEffects;
	}
	else if (key == "SFX_4")
	{
		mSFXMapList[3] = soundEffects;
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time  timeSinceLastUpdate = sf::Time::Zero;
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
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Space)
				{
					GameObjectManager::getInstance()->addObject(new EnemyCar("EnemyCar"));
				}
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

