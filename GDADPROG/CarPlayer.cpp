#include "CarPlayer.h"
#include <iostream>
#include "TextureManager.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "Game.h"
#include "Renderer.h"

CarPlayer::CarPlayer(std::string name) : AGameObject(name)
{

}

void CarPlayer::initialize()
{
	std::cout << "Declared as " << this->getName() << std::endl;

	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("Eagle"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* playerMovement = new PlayerMovement("PlayerMovement");
	this->attachComponent(playerMovement);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

	Renderer* renderer = new Renderer("PlayerSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);
}

void CarPlayer::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void CarPlayer::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);
}