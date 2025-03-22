#pragma once
#include "AbstractComponent.h"
#include "CollisionListener.h"
#include "AbstractGameObject.h"

class Collider : public AbstractComponent {
public:
	Collider(std::string name);

	void setCollisionListener(CollisionListener* listener);
	
	void setChecked(bool flag);
	bool isChecked();

	bool willCollide(Collider* another);
	bool alreadyCollided();
	void setAlreadyCollided(bool flag);

	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect localBounds);
	void collisionEnter(AGameObject* gameObjects);
	void collisionExit(AGameObject* gameObjects);

	void perform();
private:
	bool collided = false;
	bool checked = false;
	sf::FloatRect localBounds;
	CollisionListener* listener;
};

