#include "PlayerMovement.h"
#include "CarPlayer.h"
#include "PlayerInputController.h"
#include "AbstractGameObject.h"

PlayerMovement::PlayerMovement(std::string name) : AbstractComponent(name, Script)
{

}

void PlayerMovement::perform()
{
	CarPlayer* carPlayer = (CarPlayer*)this->getOwner();
	PlayerInputController* inputController = (PlayerInputController*)(carPlayer->getComponentOfType(ComponentType::Input)[0]);
	sf::Transformable& playerTransformable = carPlayer->getTransformable();

	if (inputController == nullptr)
	{
		std::cout << "playerTransformable not found" << std::endl;
	}

	sf::Vector2f offset(0.0f, 0.0f);

	if (inputController->isUp())
	{
		offset.y -= this->SPEED_MULTIPLIER;
		playerTransformable.move(offset * deltaTime.asSeconds());
		std::cout << "Moving Up" << std::endl;
	}

	else if (inputController->isDown())
	{
		offset.y += this->SPEED_MULTIPLIER;
		playerTransformable.move(offset * deltaTime.asSeconds());
		std::cout << "Moving Down" << std::endl;
	}

	else if (inputController->isRight())
	{
		offset.x += this->SPEED_MULTIPLIER;
		playerTransformable.move(offset * deltaTime.asSeconds());
		std::cout << "Moving Right" << std::endl;
	}

	else if (inputController->isLeft())
	{
		offset.x -= this->SPEED_MULTIPLIER;
		playerTransformable.move(offset * deltaTime.asSeconds());
		std::cout << "Moving Left" << std::endl;
	}
}