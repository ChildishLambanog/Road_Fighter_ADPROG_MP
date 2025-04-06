#include <stddef.h>
#include <iostream>
#include "SFXManager.h"

SFXManager* SFXManager::sharedInstance = NULL;

void SFXManager::loadAll()
{	
	loadSound("boom", "Media/SFX/explosion_sfx.WAV");
	loadSound("score", "Media/SFX/UI_SFX.wav");
}

void SFXManager::loadSound(std::string key, std::string path)
{
	sf::SoundBuffer* sound = new sf::SoundBuffer();
	sound->loadFromFile(path);
	soundMap[key] = sound;
}

sf::SoundBuffer* SFXManager::getSound(std::string key)
{
	if (soundMap[key] != nullptr)
	{
		return soundMap[key];
	}

	else
	{
		std::cout << "No sound found for" << key << std::endl;
		return nullptr;
	}
}

SFXManager* SFXManager::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new SFXManager();
	}

	return sharedInstance;
};

void SFXManager::testFunction()
{
	std::cout << "Hi, I'm a SFX Manager singleton LMAO XD!" << std::endl;
}