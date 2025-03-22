#include "AbstractGameObject.h"
#include "GenericInputController.h"
#include "Renderer.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
}

AGameObject::~AGameObject()
{
	if (this->sprite != nullptr)
	{
		delete sprite;
	}

	for (int i = 0; i < this->componentList.size(); i++)
	{
		delete this->componentList[i];
	}

	for (int i = 0; i < this->childList.size(); i++)
	{
		delete this->childList[i];
	}
}

void AGameObject::processInput(sf::Event event)
{
	if (!this->isEnabled()) return;

	std::vector<AbstractComponent*> componentList = this->getComponentOfType(AbstractComponent::ComponentType::Input);

	for (int j = 0; j < componentList.size(); j++)
	{
		((GenericInputController*)componentList[j])->assignEvent(event);
		componentList[j]->perform();
	}

	for (int i = 0; i < this->childList.size(); i++)
	{
		childList[i]->processInput(event);
	}
}

std::string AGameObject::getName()
{
	return name;
}

void AGameObject::update(sf::Time deltaTime)
{
	if (!this->isEnabled()) return;

	std::vector<AbstractComponent*> componentList = this->getComponentOfType(AbstractComponent::ComponentType::Script);

	for (int j = 0; j < componentList.size(); j++)
	{
		componentList[j]->setDeltaTime(deltaTime);
		componentList[j]->perform();
	}

	for (int i = 0; i < this->childList.size(); i++)
	{
		AGameObject* child = this->childList[i];
		child->update(deltaTime);
	}
}

void AGameObject::attachComponent(AbstractComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AbstractComponent* component)
{
	int index = -1;

	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i] == component)
		{
			index = i;
			this->componentList[i]->detachOwner();
			break;
		}
	}

	if (index != -1)
	{
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AbstractComponent* AGameObject::findComponentByName(std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getName() == name)
		{
			return this->componentList[i];
		}
	}

	return NULL;
}

AbstractComponent* AGameObject::findComponentOfType(AbstractComponent::ComponentType type, std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type)
		{
			return this->componentList[i];
		}
	}

	return NULL;
}

std::vector<AbstractComponent*> AGameObject::getComponentOfType(AbstractComponent::ComponentType type)
{
	std::vector<AbstractComponent*> foundList;

	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getType() == type)
		{	
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

std::vector<AbstractComponent*> AGameObject::getComponentsOfTypeRecursive(AbstractComponent::ComponentType type)
{
	std::vector<AbstractComponent*> foundList;
	
	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getType() == type)
		{
			foundList.push_back(this->componentList[i]);
		}
	}

	for (int i = 0; i < this->childList.size(); i++)
	{
		foundList = this->getComponentRecursiveProper(this->childList[i], type, foundList);
	}

	return foundList;
}

void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	if (!this->isEnabled()) return;

	renderStates.transform = renderStates.transform * this->transformable.getTransform();

	if (sprite != nullptr)
	{
		targetWindow->draw(*sprite, renderStates);
	}

	std::vector<AbstractComponent*> componentList = this->getComponentOfType(AbstractComponent::ComponentType::Renderer);

	for (int j = 0; j < componentList.size(); j++)
	{
		Renderer* renderer = (Renderer*)componentList[j];
		renderer->assignTargetWindow(targetWindow);
		renderer->setRenderStates(renderStates);
		renderer->perform();
	}

	for (int i = 0; i < this->childList.size(); i++)
	{
		AGameObject* child = this->childList[i];
		child->draw(targetWindow, renderStates);
	}
}

void AGameObject::attachChild(AGameObject* child)
{
	this->childList.push_back(child);
	child->setParent(this);
	child->initialize();
}

void AGameObject::detachChild(AGameObject* child)
{
	int index = -1;

	for (int i = 0; i < this->childList.size(); i++)
	{
		if (this->childList[i] == child)
		{
			index = i;
		}
	}

	if (index != -1)
	{
		this->childList.erase(this->childList.begin() + index);
		this->childList.shrink_to_fit();
	}
}

void AGameObject::setPosition(float x, float y)
{
	this->transformable.setPosition(x, y);
}


std::vector<AbstractComponent*> AGameObject::getComponentRecursiveProper(AGameObject* object, AbstractComponent::ComponentType type, std::vector<AbstractComponent*> foundList)
{
	for (int i = 0; i < object->componentList.size(); i++)
	{
		if (object->componentList[i]->getType() == type)
		{
			foundList.push_back(object->componentList[i]);
		}
	}

	for (int i = 0; i < object->childList.size(); i++)
	{
		foundList = this->getComponentRecursiveProper(object->childList[i], type, foundList);
	}

	return foundList;
}


sf::Transformable& AGameObject::getTransformable()
{
	return transformable;
}

void AGameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}

AGameObject* AGameObject::getParent()
{
	return this->mParent;
}

void AGameObject::setParent(AGameObject* parent)
{
	this->mParent = parent;
}

sf::Transform AGameObject::getGlobalTransform()
{
	AGameObject* parentObj = this;
	std::vector<AGameObject*> parentList;

	while (parentObj != NULL)
	{
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;

	for (int i = startIdx; i >= 0; i--)
	{
		transform = transform * parentList[i]->getTransformable().getTransform();
	}

	return transform;
}