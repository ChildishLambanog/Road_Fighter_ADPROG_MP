#include "TextureManager.h"
#include <iostream>
#include <stddef.h>

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::loadAll() //implement later
{
	
}

void TextureManager::loadTexture(std::string key, std::string path)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textureMap[key] = texture;
}

sf::Texture* TextureManager::getTexture(std::string key)
{
	if (textureMap[key] != nullptr)
	{
		return textureMap[key];
	}

	else
	{
		std::cout << "No texture found for " << key << std::endl;
		return nullptr;
	}
}

TextureManager* TextureManager::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new TextureManager();
	}

	return sharedInstance;
}

void TextureManager::testFunction()
{
	std::cout << "Hi, I'm a Texture Manager singleton LMAO XD!" << std::endl;
}
