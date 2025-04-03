#pragma once
#include "AbstractGameObject.h"
#include "AbstractPoolable.h"
#include "CollisionListener.h"
#include "Collider.h"
class EnemyCar : public AbstractPoolable, public CollisionListener
{
public:
	EnemyCar(std::string name);
	~EnemyCar();
	void initialize();
	//pool
	void onRelease();
	void onActivate();
	AbstractPoolable* clone();
	//collision
	void onCollisionEnter(AGameObject* other);
	void onCollisionExit(AGameObject* other);
private:
	sf::Sprite* sprite = new sf::Sprite();
	int counter = 0;

	const int SPAWN_RANGE = 300;
	
	Collider* collider;
};