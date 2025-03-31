#include "ObjectPoolHolder.h"

const std::string ObjectPoolHolder::ENEMY_POOL_TAG = "EnemyPool";
//const std::string ObjectPoolHolder::TRUCK_POOL_TAG = "Truckpool";
//const std::string ObjectPoolHolder::CAR_POOL_TAG = "CarPool";
//const std::String ObjectPoolHolder::GAS_POOL_TAG = "BulletPool";
ObjectPoolHolder* ObjectPoolHolder::sharedInstance = nullptr;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new ObjectPoolHolder();
	}

	return sharedInstance;
}

void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->getTag()] = pool;
}

void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->getTag());
	delete pool;
}

GameObjectPool* ObjectPoolHolder::getPool(std::string tag)
{
	return this->poolMap[tag];
}