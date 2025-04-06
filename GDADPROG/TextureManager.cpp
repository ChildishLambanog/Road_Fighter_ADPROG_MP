#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::loadAll()
{
	loadTexture("desert_bg", "Media/Textures/Road_Design.png");
	sf::Texture* bgTex;
	bgTex = getTexture("desert_bg");
	bgTex->setRepeated(true);
	loadTexture("Eagle", "Media/Textures/Player_Car.png"); //Player
	loadTexture("Avenger", "Media/Textures/Enemy_Car1.png"); //Enemy Car 1
	loadTexture("title_bg", "Media/Textures/f.png");
	loadTexture("btn_normal", "Media/Textures/b_4.png");
	loadTexture("btn_pressed", "Media/Textures/b_5.png");
	loadTexture("bar_1", "Media/Textures/bar_1.png");
	loadTexture("title_screen", "Media/UI/TitleScreenBG.png"); //Title Screen
	loadTexture("GameOver_Screen", "Media/UI/Game_Over_Screen_BG.png"); //Game Over Screen
	loadTexture("game_over", "Media/UI/GameOver.png");
	loadTexture("skull", "Media/UI/Skull.png");

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
}; 

void TextureManager::testFunction()
{
	std::cout << "Hi, I'm a Texture Manager singleton LMAO XD!" << std::endl;
}
