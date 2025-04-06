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
#include "ScoreManager.h"

Game::Game() : mWindow(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "Rameses Amar & Ira Villanueva"), mSampleEntity()
{
	ApplicationManager::getInstance()->initialize(&mWindow);
	TextureManager::getInstance()->loadAll();
	FontManager::getInstance()->loadAll();
	SFXManager::getInstance()->loadAll();
	SceneManager::getInstance()->registerScene(new GameScene());
	TitleMenuScreen* titleMenu = new TitleMenuScreen("TitleMenuScreen");
	GameObjectManager::getInstance()->addObject(titleMenu);

	font = FontManager::getInstance()->getFont("default");

	scoreText.setFont(*font);
	scoreText.setCharacterSize(100);
	scoreText.setFillColor(sf::Color::Green);
	scoreText.setPosition(250, 200);

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

	
	if (key == "SFX_1")
	{
		mSFXMapList[0] = soundEffects;

	}
	else if (key == "SFX_2")
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
        if (elapsedTime.asSeconds() >= 1.f && SceneManager::getInstance()->getActiveScene() == SceneManager::GAME_SCENE_NAME)
        {
        ScoreManager::getInstance()->addScore();
        elapsedTime = sf::Time::Zero; // Reset elapsed time
		scoreText.setString("Score: " + std::to_string(ScoreManager::getInstance()->getScore()));

        }
		
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
	mWindow.draw(scoreText);
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

