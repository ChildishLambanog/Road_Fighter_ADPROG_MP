#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class AGameObject; 

class AbstractComponent {
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input  = 2, Physics = 3};
	AbstractComponent(std::string name, ComponentType type);
	virtual ~AbstractComponent();

	void attachOwner(AGameObject* owner);
	void detachOwner();
	AGameObject* getOwner();
	ComponentType getType();
	std::string getName();

	void setDeltaTime(sf::Time deltaTime);
	virtual void perform() = 0;
protected:
	AGameObject* owner;
	ComponentType type;
	std::string name;
	sf::Time deltaTime;
};