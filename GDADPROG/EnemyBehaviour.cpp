#include "EnemyBehaviour.h"
#include "AbstractGameObject.h"
#include "Game.h"
#include "ObjectPoolHolder.h"
#include <SFML/Graphics.hpp>

EnemyBehaviour::EnemyBehaviour(std::string name) : AbstractComponent(name, Script)
{
	this->reset();
}

void EnemyBehaviour::perform() //copy of this can be found below
{
	this->tick += this->deltaTime.asSeconds();
	sf::Transformable& transformable = this->getOwner()->getTransformable();

	if (this->tick > this->forwardDuration && this->movementType != Side)
	{
		int counter = (this->movementType + 1);
	}

	if (this->movementType == Forward)
	{
		transformable.move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
	}

	if (this->movementType == SlowForward)
	{
		transformable.move(0, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER / 2.0f));
	}

	isItOutOfBounds(); //calls the function to check if the enemy goes out of bounds
}

void EnemyBehaviour::isItOutOfBounds()
{
	sf::Vector2f currentPos = this->getOwner()->getTransformable().getPosition();

	if (currentPos.y > Game::WINDOW_HEIGHT + 20) //checks if enemy curren Y position is out of bounds if true it calls release poolable
	{
		ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG)->releasePoolable((AbstractPoolable*)this->getOwner());
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
	this->forwardDuration = (rand() % 3) + 4.5f; //(rand() % 3) + 1.0f
}




//void EnemyBehaviour::perform() //copy of this can be found below
//{
//	this->tick += this->deltaTime.asSeconds();
//	sf::Transformable& transformable = this->getOwner()->getTransformable();

	//if (this->tick > this->forwardDuration && this->movementType != Side)
	//{
	//	int counter = (this->movementType + 1); //% EnemyMovementType::Side + 1;
	//	this->movementType = (EnemyMovementType)counter;
	//}

	//if (this->movementType == Forward)
	//{
	//	transformable.move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
	//}

	//if (this->movementType == SlowForward)
	//{
	//	transformable.move(0, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER / 2.0f));
	//}

	//else if (this->movementType == Side)
	//{
	//	static float currentPosX = this->getOwner()->getTransformable().getPosition().x;

	//	if (transformable.getPosition().x > Game::WINDOW_WIDTH / 2)
	//	{
	//		transformable.move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
	//		
	//		if (transformable.getPosition().x > transformable.getPosition().x + 10 || transformable.getPosition().x < transformable.getPosition().x - 10)
	//		{
	//			//If the enemy reaches the range limit, change the movement type back to Forward
	//			this->movementType = Forward;
	//		}
	//	}

	//	else
	//	{
	//		transformable.move(-this->deltaTime.asSeconds() * SPEED_MULTIPLIER * 1.5, 0);
	//	}

	//}
//
//	isItOutOfBounds(); //calls the function to check if the enemy goes out of bounds
//}

