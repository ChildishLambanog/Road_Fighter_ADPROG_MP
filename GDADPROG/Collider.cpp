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

void Collider::setChecked(bool flag)
{
	this->checked = flag;
}

bool Collider::isChecked()
{
	return this->checked;
}

bool Collider::willCollide(Collider* another)
{
	sf::FloatRect A = this->getGlobalBounds();
	sf::FloatRect B = another->getGlobalBounds();

	return A.intersects(B);
}

bool Collider::alreadyCollided()
{
	return this->collided;
}

void Collider::setAlreadyCollided(bool flag)
{
	this->collided = flag;
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