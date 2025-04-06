#include "MainMenuScreen.h"
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
#include <iostream>
#include <string>

MainMenuScreen::MainMenuScreen(std::string name) : AGameObject(name), ButtonListener()
{
}

void MainMenuScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("title_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	this->transformable.setScale(sf::Vector2f(0.7f, 0.7f));

	UIText* titleText = new UIText("text_1");
	this->attachChild(titleText);
	titleText->setPosition(10, -50);
	titleText->setSize(45);
	titleText->setText("Are you sure you want \n to return to the main menu? ");

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setPosition(-150, 110);
	button1->getTransformable().setScale(0.3f, 0.3f);
	button1->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button1->attachChild(button_1Text);
	button_1Text->setPosition(0, -20);
	button_1Text->setSize(100);
	button_1Text->setText("YES");

	UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setPosition(150, 110);
	button2->getTransformable().setScale(0.3f, 0.3f);
	button2->setButtonListener(this);

	UIText* button_2Text = new UIText("text_1");
	button2->attachChild(button_2Text);
	button_2Text->setPosition(0, -20);
	button_2Text->setSize(100);
	button_2Text->setText("NO");
}

void MainMenuScreen::onButtonClicked(UIButton* button)
{
	std::cout << button->getName();
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{
	std::cout << button->getName();

	ApplicationManager* UIManager = ApplicationManager::getInstance();
	SceneManager* scene = SceneManager::getInstance();

	if (button->getName() == "button_1")
	{
		GameObjectManager::getInstance()->deleteAllObjectsInScene();
		scene->unloadScene();
		scene->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
	}

	else if (button->getName() == "button_2")
	{
		UIManager->resumeApplication();
		AGameObject* flag = GameObjectManager::getInstance()->findObjectByName("MainMenuScreen");
		flag->setEnabled(false);
	}
}