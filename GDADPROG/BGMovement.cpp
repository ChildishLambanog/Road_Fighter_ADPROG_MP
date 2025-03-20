#include "BGMovement.h"
#include "BGObject.h"

BGMovement::BGMovement(std::string name) : AbstractComponent(name, Script)
{
}

void BGMovement::perform()
{
	BGObject* bgObj = (BGObject*)this->getOwner();
	sf::Sprite* sprite = bgObj->getSprite();
	
	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += SPEED_MULTIPLIER;

	sprite->move(offset * deltaTime.asSeconds());

	sf::Vector2f localPos = sprite->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0)
	{
		sprite->setPosition(0, -Game::WINDOW_HEIGHT * 7);
	}
}