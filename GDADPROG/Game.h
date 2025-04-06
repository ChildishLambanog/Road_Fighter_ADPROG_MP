#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

class Game {
public:
	Game();
	void run();
	static const int WINDOW_WIDTH = 950;
	static const int WINDOW_HEIGHT = 730;
	float PlayerSpeed = 300.f;
	int fpsCount = 0;
	int fps = 60;
	const sf::Time  TimePerFrame = sf::seconds(1.f / 60.f);
private:
	void processEvents();
	void update(sf::Time);
	void render();
	void addEntity(std::string key, float x, float y);
	void addSFX(std::string key);
private:
	sf::RenderWindow mWindow;
	Entity mSampleEntity;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::Font* font;
	sf::Text scoreText;

	sf::Text deadText;


	sf::Text textFps;
	sf::Text textUpdaterPerS;
	sf::Sound mSFX;
	std::unordered_map<int, sf::SoundBuffer*> mSFXMapList;
	std::vector<Entity*> mEntityList;
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;
	bool mIsMouseLMBPressed = false;
	bool mIs1Pressed = false;
	bool mIs2Pressed = false;
	bool mIs3Pressed = false;
	bool mIs4Pressed = false;
};