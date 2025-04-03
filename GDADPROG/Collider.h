#pragma once
#include "AbstractComponent.h"
#include "CollisionListener.h"
#include "AbstractGameObject.h"
#include "unordered_set"

class Collider : public AbstractComponent {
public:
	Collider(std::string name);

	void setCollisionListener(CollisionListener* listener);
	
	

	bool willCollide(Collider* another);
	bool hasCollisionWith(Collider* collider);
	void addCollision(Collider* collider);
	void removeCollision(Collider* collider);



	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect localBounds);
	void collisionEnter(AGameObject* gameObjects);
	void collisionExit(AGameObject* gameObjects);

	void perform();
	void clearCollisions();
private:
	std::unordered_set<Collider*>collisions;
	bool checked = false;
	sf::FloatRect localBounds;
	CollisionListener* listener;
};

