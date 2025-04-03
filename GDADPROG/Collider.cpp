#include "Collider.h"
#include "AbstractGameObject.h"
#include "PhysicsManager.h"
#include <iostream>

Collider::Collider(std::string name) : AbstractComponent(name, AbstractComponent::Physics)
{

}

void Collider::setCollisionListener(CollisionListener* listener)
{
	this->listener = listener;
}

bool Collider::hasCollisionWith(Collider* collider)
{
	return this->collisions.find(collider) != this->collisions.end();
}


void Collider::addCollision(Collider* collider)
{
	this->collisions.insert(collider);
}

void Collider::removeCollision(Collider* collider)
{

	this->collisions.erase(collider);
}

void Collider::clearCollisions()
{
	for (Collider* collider : this->collisions)
	{
		collider->collisionExit(this->getOwner());
		this->collisionExit(collider->getOwner());
		collider->removeCollision(this);
	}
	collisions.clear();
}

bool Collider::willCollide(Collider* another)
{
	sf::FloatRect A = this->getGlobalBounds();
	sf::FloatRect B = another->getGlobalBounds();

	return A.intersects(B);
}

void Collider::setLocalBounds(sf::FloatRect localBounds)
{
	this->localBounds = localBounds;
}

void Collider::collisionEnter(AGameObject* gameObjects)
{
	if (this->listener != nullptr)
	{
		this->listener->onCollisionEnter(gameObjects);
	}
}

void Collider::collisionExit(AGameObject* gameObjects)
{
	if (this->listener != nullptr)
	{
		this->listener->onCollisionExit(gameObjects);
	}
}

sf::FloatRect Collider::getGlobalBounds()
{
	return this->getOwner()->getGlobalTransform().transformRect(this->localBounds);
}

void Collider::perform()
{
}