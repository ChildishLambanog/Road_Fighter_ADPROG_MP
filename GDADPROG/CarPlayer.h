#pragma once
#include "AbstractGameObject.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "CollisionListener.h"


class CarPlayer : public AGameObject,public CollisionListener
{
public:
	CarPlayer(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* contact);

	//sf::Transformable& getTransformable();
	//sf::Drawable* getSprite();

private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	
	Collider* collider;
};