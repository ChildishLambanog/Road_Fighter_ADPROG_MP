#include "GameObjectPool.h"
#include "GameObjectManager.h"
#include <iostream>

GameObjectPool::GameObjectPool(std::string tag, AbstractPoolable* poolableCopy, int poolableSize, AGameObject* parent)
{
	this->tag = tag;
	this->objectCopy = poolableCopy;
	this->maxPoolSize = poolableSize;
	this->parent = parent;
}

GameObjectPool::~GameObjectPool()
{
	delete this->objectCopy;
	this->objectCopy = nullptr;
	this->parent = nullptr;
}

void GameObjectPool::initialize()
{
	for (int i = 0; i < this->maxPoolSize; i++)
	{
		AbstractPoolable* poolableObject = this->objectCopy->clone();

		if (this->parent != nullptr)
		{
			this->parent->attachChild(poolableObject);
		}

		else
		{
			GameObjectManager::getInstance()->addObject(poolableObject);
		}

		poolableObject->setEnabled(false);
		this->availableObjects.push_back(poolableObject);
	}
}

bool GameObjectPool::hasObjectAvailable(int requestSize)
{
	return requestSize <= this->availableObjects.size();
}

AbstractPoolable* GameObjectPool::requestPoolable()
{
	if (this->hasObjectAvailable(1))
	{
		AbstractPoolable* poolableObject = this->availableObjects[this->availableObjects.size() - 1];
		this->availableObjects.erase(this->availableObjects.begin() + this->availableObjects.size() - 1);
		this->usedObjects.push_back(poolableObject);

		//std::cout << "Requested object. Available: " << this->availableObjects.size() << "Used: " << this->usedObjects.size() << std::endl;
		this->setEnabled(poolableObject, true);
		return poolableObject;
	}

	else
	{
		//std::cerr << "No more poolable " << this->objectCopy->getName() << " available!" << std::endl;
		return NULL;
	}
}

std::vector<AbstractPoolable*> GameObjectPool::requestPoolableBatch(int size)
{
	std::vector<AbstractPoolable*> returnList;

	if (this->hasObjectAvailable(size))
	{
		for (int i = 0; i < size; i++)
		{
			returnList.push_back(this->requestPoolable());
		}
	}

	else
	{
		std::cerr << "Insufficient " << this->objectCopy->getName() << " available in pool. " << "Count is: " << this->availableObjects.size() << " while request is " << size << std::endl;
	}
	return returnList;
}

std::string GameObjectPool::getTag()
{
	return this->tag;
}

void GameObjectPool::setEnabled(AbstractPoolable* poolableObject, bool flag)
{
	if (flag)
	{
		poolableObject->setEnabled(true);
		poolableObject->onActivate();
	}

	else
	{
		poolableObject->setEnabled(false);
		poolableObject->onRelease();
	}
}

void GameObjectPool::releasePoolable(AbstractPoolable* poolableObject)
{
	for (int i = 0; i < usedObjects.size(); i++)
	{
		if (usedObjects[i] == poolableObject)
		{
			usedObjects.erase(usedObjects.begin() + i);
			availableObjects.push_back(poolableObject);
			setEnabled(poolableObject, false);
		}
	}
}

void GameObjectPool::releasePoolableBatch(std::vector<AbstractPoolable*> objectList)
{
	for (int i = 0; i < objectList.size(); i++)
	{
		this->releasePoolable(objectList[i]);
	}
}

void GameObjectManager::deleteAllObjectsInScene()
{
	for (int i = 0; i < this->mGameObjectList.size(); i++)
	{
		delete this->mGameObjectList[i];
	}

	this->mGameObjectList.clear();
	this->mGameObjectList.shrink_to_fit();
	this->mGameObjectMap.clear();
}