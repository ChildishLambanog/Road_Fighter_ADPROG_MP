#include "EnemyCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehaviour.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "PhysicsManager.h"

EnemyCar::EnemyCar(std::string name) : AbstractPoolable(name),CollisionListener()
{
}

EnemyCar::~EnemyCar()
{
	delete this->sprite;
}

void EnemyCar::initialize()
{
	this->sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("Avenger"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	this->getTransformable().move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
	this->getTransformable().setRotation(180);

	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	EnemyBehaviour* behaviour = new EnemyBehaviour("EnemyBehaviour");
	this->attachComponent(behaviour);
	behaviour->configure(1.0f);

	this->collider = new Collider("EnemyCollider");
	this->collider->setLocalBounds(sprite->getLocalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	PhysicsManager::getInstance()->initialize("physManger",this);


}

void EnemyCar::onRelease()
{
	PhysicsManager::getInstance()->untrackObject(this->collider);
}

void EnemyCar::onActivate()
{
	EnemyBehaviour* behaviour = (EnemyBehaviour*)this->findComponentByName("EnemyBehaviour");
	behaviour->reset();

	PhysicsManager::getInstance()->trackObject(this->collider);

	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	this->getTransformable().move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
}

AbstractPoolable* EnemyCar::clone()
{
	AbstractPoolable* copyObj = new EnemyCar(this->name);
	return copyObj;
}

void EnemyCar::onCollisionEnter(AGameObject* contact)
{
	//std::cout << "collided with " << contact->getName()<<std::endl;
	if (contact->getName().find("CarObject")!=std::string::npos)
	{
		std::cout << "collided with " << contact->getName();
		return;
		GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
		enemyPool->releasePoolable((AbstractPoolable*)this);
	}

}


void EnemyCar::onCollisionExit(AGameObject* contact)
{
	std::cout << "no";
}