#include "GameOverScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "UIButton.h"
#include "UIText.h"
#include "ApplicationManager.h"
#include "AbstractGameObject.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "TitleScreenExit.h"
#include <iostream>
#include <string>

GameOverScreen::GameOverScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void GameOverScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("GameOver_Screen"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("GameOver_Screen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	this->transformable.setScale(sf::Vector2f(0.925f, 0.925f));

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* playButton = new UIButton("main_menu_button", btnNormal, btnPressed);
	this->attachChild(playButton);
	playButton->setPosition(-320, 315);
	playButton->getTransformable().setScale(0.35f, 0.35f);
	playButton->setButtonListener(this);

	UIText* playButtonText = new UIText("text_play");
	playButton->attachChild(playButtonText);
	playButtonText->setPosition(0, -20);
	playButtonText->setSize(80);
	playButtonText->setText("MAIN MENU");

	UIButton* titleQuitButton = new UIButton("quit_button", btnNormal, btnPressed);
	this->attachChild(titleQuitButton);
	titleQuitButton->setPosition(320, 315);
	titleQuitButton->getTransformable().setScale(0.35f, 0.35f);
	titleQuitButton->setButtonListener(this);

	UIText* titleQuitText = new UIText("text_quit_title");
	titleQuitButton->attachChild(titleQuitText);
	titleQuitText->setPosition(0, -20);
	titleQuitText->setSize(100);
	titleQuitText->setText("QUIT");

	SceneManager::getInstance()->registerScene(new MainMenuScene());
	SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
}

void GameOverScreen::onButtonClicked(UIButton* button)
{
	std::cout << button->getName();
}

void GameOverScreen::onButtonReleased(UIButton* button)
{
	std::cout << button->getName();

	ApplicationManager* UIManager = ApplicationManager::getInstance();
	SceneManager* sceneManager = SceneManager::getInstance();


	if (button->getName() == "main_menu_button")
	{
		GameObjectManager::getInstance()->deleteAllObjectsInScene();
		sceneManager->unloadScene();
		sceneManager->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
	}

	else if (button->getName() == "quit_button")
	{
		UIManager->applicationQuit();
	}

}