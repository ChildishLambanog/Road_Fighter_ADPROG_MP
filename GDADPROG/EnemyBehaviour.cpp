#include "EnemyBehaviour.h"
#include "AbstractGameObject.h"
#include "Game.h"
#include "ObjectPoolHolder.h"
#include <SFML/Graphics.hpp>

EnemyBehaviour::EnemyBehaviour(std::string name) : AbstractComponent(name, Script)
{
	this->reset();
}

void EnemyBehaviour::perform()
{
	this->tick += this->deltaTime.asSeconds();
	sf::Transformable& transformable = this->getOwner()->getTransformable();

	if (this->tick > this->forwardDuration && this->movementType != Side)
	{
		int counter = (this->movementType + 1) % EnemyMovementType::Side + 1;
		this->movementType = (EnemyMovementType)counter;
	}

	if (this->movementType == Forward)
	{
		transformable.move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
	}

	if (this->movementType == SlowForward)
	{
		transformable.move(0, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER / 2.0f));
	}

	else if (this->movementType == Side)
	{
		if (transformable.getPosition().x > Game::WINDOW_WIDTH / 2)
		{
			transformable.move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
		}

		else
		{
			transformable.move(-this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
		}

		if (transformable.getPosition().x > Game::WINDOW_WIDTH + 20 || transformable.getPosition().x < -20)
		{
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG)->releasePoolable((AbstractPoolable*)this->getOwner());
		}
	}
}

void EnemyBehaviour::configure(float delay)
{
	this->delay = delay;
}

void EnemyBehaviour::reset()
{
	this->tick = 0.0f;
	this->movementType = Forward;
	this->forwardDuration = (rand() % 3) + 1.0f;
}

