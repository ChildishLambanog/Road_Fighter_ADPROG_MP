#include "TitleScreenExit.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "UIButton.h"
#include "UIText.h"
#include "ApplicationManager.h"
#include "AbstractGameObject.h"
#include "SceneManager.h"
#include <iostream>
#include <string>

TitleScreenExit::TitleScreenExit(std::string name) : AGameObject(name), ButtonListener()
{
}

void TitleScreenExit::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("title_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("TitleMainMenuScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	this->transformable.setScale(0.7f, 0.7f);

	UIText* titleMenuText = new UIText("TitleMainMenuText");
	this->attachChild(titleMenuText);
	titleMenuText->setPosition(0, -50);
	titleMenuText->setSize(40);
	titleMenuText->setText("Are you sure you want \n to quit the game ? ");

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* title_button_1 = new UIButton("title_button_1", btnNormal, btnPressed);
	this->attachChild(title_button_1);
	title_button_1->setPosition(-200, 150);
	title_button_1->getTransformable().setScale(0.3f, 0.3f);
	title_button_1->setButtonListener(this);

	UIText* title_button_1_Text = new UIText("text_1");
	title_button_1->attachChild(title_button_1_Text);
	title_button_1_Text->setPosition(0, -20);
	title_button_1_Text->setSize(100);
	title_button_1_Text->setText("YES");

	UIButton* title_button_2 = new UIButton("title_button_2", btnNormal, btnPressed);
	this->attachChild(title_button_2);
	title_button_2->setPosition(200, 150);
	title_button_2->getTransformable().setScale(0.3f, 0.3f);
	title_button_2->setButtonListener(this);

	UIText* title_button_2_Text = new UIText("text_2");
	title_button_2->attachChild(title_button_2_Text);
	title_button_2_Text->setPosition(0, -20);
	title_button_2_Text->setSize(100);
	title_button_2_Text->setText("NO");
}

void TitleScreenExit::onButtonClicked(UIButton* button)
{
	std::cout << button->getName();
}

void TitleScreenExit::onButtonReleased(UIButton* button)
{
	std::cout << button->getName();

	ApplicationManager* UIManager = ApplicationManager::getInstance();


	if (button->getName() == "title_button_1")
	{
		UIManager->applicationQuit();
	}

	else if (button->getName() == "title_button_2")
	{
		SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
		UIManager->resumeApplication();
		AGameObject* flag = GameObjectManager::getInstance()->findObjectByName("TitleScreenExit");
		flag->setEnabled(false);
	}

}