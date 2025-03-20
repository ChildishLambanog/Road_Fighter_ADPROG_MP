#pragma once
#include "AbstractGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>

class BGObject : public AGameObject
{
public:
	BGObject(std::string name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
	sf::Sprite* getSprite();
	sf::Sprite* sprite;

private:
	const float SPEED_MULTIPLIER = 100.f;
};