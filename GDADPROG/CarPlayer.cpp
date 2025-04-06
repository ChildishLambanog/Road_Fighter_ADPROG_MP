#include "CarPlayer.h"
#include <iostream>
#include "TextureManager.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "Game.h"
#include "Renderer.h"

CarPlayer::CarPlayer(std::string name) : AGameObject(name), CollisionListener()
{}

void CarPlayer::initialize()
{
	std::cout << "Declared as " << this->getName() << std::endl;

	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("Eagle"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->transformable.setPosition(755, 650); //original spawn (500, 650), max left (230,650), max right (755, 650)

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* playerMovement = new PlayerMovement("PlayerMovement");
	this->attachComponent(playerMovement);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

	Renderer* renderer = new Renderer("PlayerSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	/*sf::FloatRect globalBounds = sprite->getGlobalBounds();*/ //test later

	this->collider = new Collider("playerCollider");
	this->collider->setLocalBounds(sprite->getLocalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	PhysicsManager::getInstance()->initialize("physManger", this);
	PhysicsManager::getInstance()->trackObject(this->collider);

}

void CarPlayer::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void CarPlayer::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);
}

void CarPlayer::onCollisionEnter(AGameObject* contact)
{

	if (contact->getName().find("enemy") != std::string::npos)
	{
		contact->
		
	
	}

}

void CarPlayer::onCollisionExit(AGameObject* contact)
{
	std::cout << "[melr";

}