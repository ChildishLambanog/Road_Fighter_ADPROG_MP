#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

class SFXManager {
public:
	static SFXManager* getInstance();
	void testFunction();

	void loadAll();
	sf::SoundBuffer* getSound(std::string);
	void playSound(std::string key) {
		sf::Sound sound;
		sound.setBuffer(*getSound(key));
		sound.play();
	}

private:
	SFXManager() {};
	SFXManager(SFXManager const&) {};
	SFXManager& operator=(SFXManager const&) {};
	static SFXManager* sharedInstance;

	void loadSound(std::string, std::string);
	std::unordered_map<std::string, sf::SoundBuffer*> soundMap;
};