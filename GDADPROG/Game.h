#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

class Game {
public:
	Game();
	void run();
	static const int WINDOW_WIDTH = 1000; //placeholder value not final
	static const int WINDOW_HEIGHT = 1000; //placeholder value not final
	float PlayerSpeed = 300.0f;
	int fpsCount = 0;
	int fps = 60;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
private:
	void processEvents();
	void update(sf::Time);
	void render();
	void addEntity(std::string key, float x, float y);
	//void addSFX(std::string key); not sure if we need this
private:
	sf::RenderWindow mWindow;
	Entity mSampleEntity;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::Font font;
	sf::Sound mSFX;
	std::unordered_map<int, sf::SoundBuffer*> mSFXMapList;
	std::vector<Entity*> mEntityList;
};

