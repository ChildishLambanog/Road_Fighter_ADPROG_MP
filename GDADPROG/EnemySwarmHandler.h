#pragma once
#include "AbstractComponent.h"
#include "GameObjectPool.h"

class EnemySwarmHandler : public AbstractComponent {
public: 
	EnemySwarmHandler(int numEnemis, std::string name, AGameObject* parent);
	~EnemySwarmHandler();
	void perform();
private:
	GameObjectPool* enemyPool;
	const float SPAWN_INTERVAL = 0.25f; //0.01f 1.0f 0.7 0.4f
	float ticks = 5.5f; //0.0f 5.5f
};