#include "EnemyCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehaviour.h"

EnemyCar::EnemyCar(std::string name) : AbstractPoolable(name)
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
}

void EnemyCar::onRelease()
{
}

void EnemyCar::onActivate()
{
	EnemyBehaviour* behaviour = (EnemyBehaviour*)this->findComponentByName("EnemyBehaviour");
	behaviour->reset();

	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	this->getTransformable().move(rand() % SPAWN_RANGE - rand() % SPAWN_RANGE, 0);
}

AbstractPoolable* EnemyCar::clone()
{
	AbstractPoolable* copyObj = new EnemyCar(this->name);
	return copyObj;
}