#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "AbstractComponent.h"

class AbstractComponent;

class AGameObject {
public:
	AGameObject(std::string name);
	virtual ~AGameObject();
	virtual void initialize() = 0;
	virtual void processInput(sf::Event event);
	virtual void update(sf::Time deltaTime);
	virtual void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
	std::string getName();

	void attachComponent(AbstractComponent* component);
	void detachComponent(AbstractComponent* component);
	AbstractComponent* findComponentByName(std::string name);
	AbstractComponent* findComponentOfType(AbstractComponent::ComponentType type, std::string name);
	std::vector<AbstractComponent*> getComponentOfType(AbstractComponent::ComponentType type);
	std::vector<AbstractComponent*> getComponentsOfTypeRecursive(AbstractComponent::ComponentType type);
	void attachChild(AGameObject* child);
	void detachChild(AGameObject* child);
	void setPosition(float x, float y);
	sf::Transformable& getTransformable();
	void setEnabled(bool flag);
	bool isEnabled();
	AGameObject* getParent();


protected:
	void setParent(AGameObject* gameObject);
	sf::Transformable transformable;
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	std::vector<AGameObject*> childList;

	std::vector<AbstractComponent*> componentList;

private:
	std::vector<AbstractComponent*> getComponentRecursiveProper(
		AGameObject* object,
		AbstractComponent::ComponentType type,
		std::vector<AbstractComponent*> foundList);
	bool enabled = true;
	AGameObject* mParent;
};

