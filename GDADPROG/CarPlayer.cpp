#include "CarPlayer.h"
#include <iostream>
#include "TextureManager.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "Game.h"
#include "Renderer.h"
#include "SFXManager.h"

#include "ScoreManager.h"

CarPlayer::CarPlayer(std::string name) : AGameObject(name), CollisionListener()
{}

void CarPlayer::initialize()
{
	std::cout << "Declared as " << this->getName() << std::endl;

	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getTexture("Eagle"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->transformable.setPosition(500, 650); //original spawn (500, 650), max left (230,650), max right (755, 650)

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* playerMovement = new PlayerMovement("PlayerMovement");
	this->attachComponent(playerMovement);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

	Renderer* renderer = new Renderer("PlayerSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	this->collider = new Collider("playerCollider");
	this->collider->setLocalBounds(sprite->getLocalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	PhysicsManager::getInstance()->initialize("physManger", this);
	PhysicsManager::getInstance()->trackObject(this->collider);
	this->cFX.setBuffer(*SFXManager::getInstance()->getSound("boom"));
	this->cFX.setVolume(10.f);
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
		cFX.play();

		if (health > 1)
		{
			ScoreManager::getInstance()->addDeath();

			std::cout << "collided with " << contact->getName() << std::endl;
			health -= 1;
			int healthShown = health;
			std::cout << "Health Remaining: " << healthShown << std::endl;
			this->transformable.setPosition(500, 650); //original spawn (500, 650)
			
		}

		else if (health == 1)
		{
			std::cout << "Game Over" << std::endl;
			ScoreManager::getInstance()->addDeath();
			AGameObject* flag = GameObjectManager::getInstance()->findObjectByName("GameOverScreen");
			ScoreManager::getInstance()->setFlag(true);
			flag->setEnabled(true);
			ApplicationManager* UIManager = ApplicationManager::getInstance();
			UIManager->pauseApplication();
		}
	}
}

void CarPlayer::onCollisionExit(AGameObject* contact)
{
	

}
int CarPlayer::getHealth()
{
	return health;
}