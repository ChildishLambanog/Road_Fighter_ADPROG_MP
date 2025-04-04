#pragma once
#include "AbstractPoolable.h"
#include <vector>

class GameObjectPool {
public:
	GameObjectPool(std::string name, AbstractPoolable* poolableCopy, int poolableSize, AGameObject* parent);
	~GameObjectPool();
	void initialize();
	bool hasObjectAvailable(int requestSize);
	AbstractPoolable* requestPoolable();
	std::vector<AbstractPoolable*> requestPoolableBatch(int size);

	void releasePoolable(AbstractPoolable* poolableObject);
	void releasePoolableBatch(std::vector<AbstractPoolable*> objectList);

	std::string getTag();
private:
	std::string tag;
	AbstractPoolable* objectCopy = NULL;
	AGameObject* parent = NULL;
	int maxPoolSize = 20;
	std::vector<AbstractPoolable*> availableObjects;
	std::vector<AbstractPoolable*> usedObjects;

	void setEnabled(AbstractPoolable* poolableObject, bool flag);
};