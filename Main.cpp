#include "Game.h"
#include "MySingletonClass.h"
#include "SFXManager.h"
#include "TextureManager.h"

int main() 
{
	TextureManager::getInstance()->testFunction();
	SFXManager::getInstance()->testFunction();
    Game game;
    game.run();
}

