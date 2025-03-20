#include "BGObject.h"
#include "BGMovement.h"

BGObject::BGObject(std::string name) : AGameObject(name)
{
	initialize();
}

void BGObject::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 8));
	sprite->setPosition(0, -Game::WINDOW_HEIGHT * 7);

	BGMovement* bgMovement = new BGMovement("BGMovement");
	this->attachComponent(bgMovement);
}

void BGObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	targetWindow->draw(*sprite);
}

void BGObject::processInput(sf::Event event)
{
	//no implementation yet
}

void BGObject::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);

	//std::vector<AbstractComponent*> componentList = this->getComponentOfType(AbstractComponent::ComponentType::Script);

	//for (int j = 0; j < this->componentList.size(); j++)
	//{
	//	this->componentList[j]->setDeltaTime(deltaTime);
	//	this->componentList[j]->perform();
	//} 
}

sf::Sprite* BGObject::getSprite()
{
	return sprite;
}

