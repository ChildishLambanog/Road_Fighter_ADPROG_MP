#include "BarQuitButton.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "Renderer.h"
#include "TextureManager.h"
#include "ApplicationManager.h"
#include "UIButton.h"
#include "UIText.h"
#include <iostream>

BarQuitButton::BarQuitButton(std::string name) : AGameObject(name), ButtonListener()
{
	//
}

void BarQuitButton::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("bar_1"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("bar_1");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->setPosition(485, 660);
	this->transformable.setScale(0.9f, 0.9f);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* quitButton = new UIButton("quit_btn", btnNormal, btnPressed);
	this->attachChild(quitButton);
	quitButton->setPosition(160, 0);
	quitButton->getTransformable().setScale(0.17f, 0.17f);
	quitButton->setButtonListener(this);

	UIText* quitButtonText = new UIText("text_1");
	quitButton->attachChild(quitButtonText);
	quitButtonText->setPosition(0, -20);
	quitButtonText->setSize(150);
	quitButtonText->setText("QUIT");
}

void BarQuitButton::onButtonClicked(UIButton* button)
{
	std::cout << button->getName();
	quitButtonPressed = true;
}

void BarQuitButton::onButtonReleased(UIButton* button)
{
	std::cout << button->getName();

	AGameObject* flag = GameObjectManager::getInstance()->findObjectByName("MainMenuScreen");
	flag->setEnabled(true);
	ApplicationManager* UIManager = ApplicationManager::getInstance();
	UIManager->pauseApplication();
}