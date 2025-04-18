#pragma once
#include "AbstractGameObject.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "CollisionListener.h"
#include "SFML/Audio.hpp"


class CarPlayer : public AGameObject,public CollisionListener
{
public:
	CarPlayer(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void onCollisionEnter(AGameObject* contact);
	void onCollisionExit(AGameObject* contact);
	int getHealth();
	//sf::Transformable& getTransformable();
	//sf::Drawable* getSprite();
	Collider* collider;

	sf::Sound cFX;
	int health = 3;	

private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	
};